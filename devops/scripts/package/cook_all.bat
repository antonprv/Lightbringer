@echo off

setlocal

rem List of target scripts
set TargetScripts=cook_client.bat cook_game.bat cook_server.bat

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
