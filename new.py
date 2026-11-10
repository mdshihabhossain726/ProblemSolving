"""Notun problem-er file baniye dey (naming ekdom thik thakbe).

Use:
    python new.py https://codeforces.com/contest/1850/problem/A
    python new.py 1850 A
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent

if len(sys.argv) == 2:
    m = (re.search(r"/contest/(\d+)/problem/(\w+)", sys.argv[1])
         or re.search(r"/problemset/problem/(\d+)/(\w+)", sys.argv[1]))
    if not m:
        sys.exit("Link ta bujhte parlam na. Example: python new.py 1850 A")
    cid, idx = m.group(1), m.group(2).upper()
elif len(sys.argv) == 3:
    cid, idx = sys.argv[1], sys.argv[2].upper()
else:
    sys.exit("Use: python new.py 1850 A   (ba problem-er link dao)")

dest = ROOT / "codeforces" / cid / f"{idx}.cpp"
if dest.exists():
    print("Age thekei ache:", dest)
else:
    dest.parent.mkdir(parents=True, exist_ok=True)
    dest.write_text((ROOT / "template.cpp").read_text(), encoding="utf-8")
    print("Baniye dilam:", dest)
