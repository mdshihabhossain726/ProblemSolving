# Setup guide (ekbar korlei hobe)

## Step 0: Ei 3 ta jinis install koro (na thakle)
1. Git: https://git-scm.com/downloads  (shob "Next" click kore install)
2. Python: https://www.python.org/downloads  (install-er shomoy **"Add Python to PATH"** tick dao)
3. VS Code: https://code.visualstudio.com  (code likhar jonno)

## Step 1: GitHub-e repo banao
1. github.com e login koro
2. Upore **+** > **New repository**
3. Name: `ProblemSolving`, **Public**, "Add a README" **tick dio na**
4. **Create repository** click koro
5. Je page ashbe oikhane repo-r link thakbe, jemon
   `https://github.com/TOMAR_USERNAME/ProblemSolving.git`

## Step 2: Git-ke tomar nam chinie dao (ekbar)
Windows-e Start menu theke **Git Bash** (ba Command Prompt) khulo, tarpor:
```
git config --global user.name "Tomar Nam"
git config --global user.email "tomar-github-email@example.com"
```

## Step 3: Repo-ta PC-te nao
Command Prompt-e (Documents folder-e giye):
```
cd Documents
git clone https://github.com/TOMAR_USERNAME/ProblemSolving.git
```
(prothom bar GitHub login chaibe, browser-e login kore dao)

Ekhon **ei zip-er shob file** (sync_cf.py, new.py, template.cpp,
start_sync.bat, README.md, .gitignore) copy kore `Documents/ProblemSolving` folder-e rakho.

## Step 4: Prothom push
```
cd ProblemSolving
git add .
git commit -m "setup"
git push -u origin HEAD
```

## Step 5: Auto-sync chalu koro
`start_sync.bat` e **double click** koro.
Prothom bar tomar Codeforces handle chaibe, likhe Enter dao.
Tarpor window ta **khola rakho** (minimize korte paro).

## Roj-er kaj
1. Command Prompt-e (ProblemSolving folder-e) problem-er link diye file banao:
   ```
   python new.py https://codeforces.com/contest/1850/problem/A
   ```
2. `codeforces/1850/A.cpp` file ta VS Code-e khule solve koro
3. Oi code Codeforces-e submit koro
4. Accepted hole ~1 minute-e GitHub-e auto chole jabe
