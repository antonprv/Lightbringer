@echo off

call "%~dp0\..\config.bat"

set dirsToRemove=Intermediate DerivedDataCache Saved Binaries Build .vs
set filesToRemove=*.sln

echo removing intermediate files...

for %%f in (%dirsToRemove%) do (
    if exist "%ProjectRoot%\src\%%f" (
        rmdir /s /q "%ProjectRoot%\src\%%f"
    )
)

for %%f in (%filesToRemove%) do (
    del /q "%ProjectRoot%\src\%%f" 2>nul
)

echo all intermediate files removed

PAUSE
