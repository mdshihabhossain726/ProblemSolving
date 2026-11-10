#!/usr/bin/env python3
"""Auto-commit accepted Codeforces solutions to this git repo.

Usage (put this file in the root of your repo):
    python sync_cf.py --handle YOUR_HANDLE   # first run: setup, old solves are NOT committed
    python sync_cf.py                         # check once
    python sync_cf.py --watch 60              # check every 60 seconds (keep it running)
    python sync_cf.py --backfill              # first run only: also commit old accepted solves

Convention: keep your code at  codeforces/<contestId>/<index>.<ext>
    e.g.  codeforces/1850/A.cpp   codeforces/1850/B.py

How it works: the Codeforces API tells us which submissions got "OK" (Accepted).
The API does not give source code, so we commit the matching file from your own
machine, plus submissions.json (a log of accepted submissions).
"""
import argparse
import json
import re
import subprocess
import sys
import time
import datetime
import urllib.parse
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parent
STATE = ROOT / "submissions.json"
README = ROOT / "README.md"
START = "<!-- SUBMISSIONS:START -->"
END = "<!-- SUBMISSIONS:END -->"
SOL_DIR = ROOT / "codeforces"
API = "https://codeforces.com/api/user.status"

# order matters: first match wins
EXTS = [("JavaScript", "js"), ("Java", "java"), ("C++", "cpp"), ("PyPy", "py"),
        ("Python", "py"), ("Kotlin", "kt"), ("C#", "cs"), ("Rust", "rs"),
        ("GNU C", "c"), ("Go", "go")]


def ext_for(lang):
    for key, ext in EXTS:
        if key in lang:
            return ext
    return None


def git(*args, check=True):
    r = subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True)
    if check and r.returncode != 0:
        raise RuntimeError(f"git {' '.join(args)} failed: {r.stderr.strip()}")
    return r


def fetch(handle, count):
    query = urllib.parse.urlencode({"handle": handle, "from": 1, "count": count})
    req = urllib.request.Request(f"{API}?{query}", headers={"User-Agent": "cf-github-sync"})
    with urllib.request.urlopen(req, timeout=30) as resp:
        data = json.load(resp)
    if data.get("status") != "OK":
        raise RuntimeError(data.get("comment", "Codeforces API error"))
    return data["result"]


def load_state():
    if STATE.exists():
        return json.loads(STATE.read_text(encoding="utf-8"))
    return None


def save_state(state):
    STATE.write_text(json.dumps(state, indent=2, ensure_ascii=False), encoding="utf-8")


def find_solution(contest_id, index, lang):
    folder = SOL_DIR / str(contest_id)
    if not folder.is_dir():
        return None
    ext = ext_for(lang)
    if ext and (folder / f"{index}.{ext}").exists():
        return (folder / f"{index}.{ext}").relative_to(ROOT).as_posix()
    matches = sorted(folder.glob(f"{index}.*"))
    return matches[0].relative_to(ROOT).as_posix() if matches else None


def build_table(state):
    rows = [r for r in state["submissions"] if r.get("file")]
    rows.sort(key=lambda r: r["time"], reverse=True)
    out = [f"**{len(rows)}** problem{'s' if len(rows) != 1 else ''} solved", "",
           "| # | Title | Solution | Tags | Submitted |",
           "|---|-------|----------|------|-----------|"]
    for n, r in zip(range(len(rows), 0, -1), rows):
        link = f"https://codeforces.com/contest/{r['contestId']}/problem/{r['index']}"
        title = f"[{r['index']} - {r['name']}]({link})".replace("|", "\\|")
        sol = f"[{r['language']}]({r['file']})"
        tags = [f"`{t}`" for t in r.get("tags", [])]
        if r.get("rating"):
            tags.append(f"`*{r['rating']}`")
        when = datetime.datetime.fromtimestamp(r["time"]).strftime("%b/%d/%Y %H:%M")
        out.append(f"| {n} | {title} | {sol} | {' '.join(tags)} | {when} |")
    return "\n".join(out)


def update_readme(state):
    block = f"{START}\n{build_table(state)}\n{END}"
    text = README.read_text(encoding="utf-8") if README.exists() else "# ProblemSolving\n"
    if START in text and END in text:
        text = re.sub(re.escape(START) + r".*?" + re.escape(END),
                      lambda m: block, text, flags=re.S)
    else:
        text = text.rstrip() + "\n\n## Submissions\n\n" + block + "\n"
    README.write_text(text, encoding="utf-8")


def run_once(args):
    state = load_state()
    first_run = state is None
    handle = args.handle or (state or {}).get("handle")
    if not handle:
        sys.exit("Give your handle once: python sync_cf.py --handle YOUR_HANDLE")
    if first_run:
        state = {"handle": handle, "submissions": []}
    state["handle"] = handle

    count = 100000 if args.backfill else 50
    accepted = [s for s in fetch(handle, count)
                if s.get("verdict") == "OK" and "contestId" in s["problem"]]
    known = {r["id"] for r in state["submissions"]}

    for s in sorted(accepted, key=lambda x: x["creationTimeSeconds"]):
        if s["id"] in known:
            continue
        p = s["problem"]
        state["submissions"].append({
            "id": s["id"],
            "contestId": p["contestId"],
            "index": p["index"],
            "name": p["name"],
            "rating": p.get("rating"),
            "tags": p.get("tags", []),
            "language": s["programmingLanguage"],
            "time": s["creationTimeSeconds"],
            "file": None,
            # on the very first run, old solves are only recorded, not committed
            "skip": first_run and not args.backfill,
        })

    committed = 0
    for r in state["submissions"]:
        if r["file"] or r.get("skip"):
            continue
        path = find_solution(r["contestId"], r["index"], r["language"])
        if not path:
            if not r.get("warned"):
                print(f"! Accepted {r['contestId']}{r['index']} but no file found. "
                      f"Save it as codeforces/{r['contestId']}/{r['index']}.<ext>")
                r["warned"] = True
            continue
        r["file"] = path
        save_state(state)
        update_readme(state)
        msg = f"CF {r['contestId']}{r['index']} - {r['name']}"
        if r.get("rating"):
            msg += f" [{r['rating']}]"
        paths = [STATE.name, README.name, path]
        git("add", "--", *paths)
        if git("diff", "--cached", "--quiet", "--", *paths, check=False).returncode == 0:
            continue  # nothing new to commit
        git("commit", "-m", msg, "--", *paths)
        print(f"+ committed: {msg}")
        committed += 1

    save_state(state)
    update_readme(state)
    git("add", "--", README.name)
    if git("diff", "--cached", "--quiet", "--", README.name, check=False).returncode != 0:
        git("commit", "-m", "Update README", "--", README.name)
        print("+ committed: Update README")
        committed += 1
    if committed:
        git("push", "-u", "origin", "HEAD")
        print("pushed to GitHub")
    elif first_run:
        print(f"Setup done for '{handle}'. New accepted solutions will be committed automatically.")


def main():
    ap = argparse.ArgumentParser(description="Auto-commit accepted Codeforces solutions")
    ap.add_argument("--handle", help="your Codeforces handle (needed only once)")
    ap.add_argument("--watch", type=int, metavar="SEC", default=0,
                    help="keep running, check every SEC seconds (min 30)")
    ap.add_argument("--backfill", action="store_true",
                    help="first run only: also commit solutions you already solved")
    args = ap.parse_args()

    if not args.watch:
        run_once(args)
        return
    args.watch = max(args.watch, 30)
    print(f"Watching Codeforces... check every {args.watch}s. Ctrl+C to stop.")
    while True:
        try:
            run_once(args)
        except Exception as e:  # keep running on network errors
            print("error:", e)
        args.backfill = False
        time.sleep(args.watch)


if __name__ == "__main__":
    main()
