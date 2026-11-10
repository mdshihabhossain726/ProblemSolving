@echo off
cd /d "%~dp0"
if exist submissions.json goto run
set /p HANDLE=Tomar Codeforces handle likho: 
python sync_cf.py --handle %HANDLE%
:run
echo.
echo Auto-sync chalu ache. Ei window bondho korba na.
python sync_cf.py --watch 60
pause
