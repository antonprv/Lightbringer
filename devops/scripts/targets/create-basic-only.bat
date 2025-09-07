@echo off

setlocal

rem List of target scripts
set TargetScripts=create-editor-target.bat create-game-target.bat

rem Loop through each script and call it
for %%S in (%TargetScripts%) do (
    if exist "%%S" (
        echo Running %%S...
        call "%%S"
    ) else (
        echo File not found: %%S
    )
)

endlocal
echo All scripts finished.
pause
