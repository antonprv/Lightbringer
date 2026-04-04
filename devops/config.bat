@echo off

rem ============================================================
rem  config.bat — auto-detected, drop this devops\ folder into
rem  any project that follows the layout:
rem
rem    <ProjectRoot>\
rem      src\          ← contains MyGame.uproject
rem      devops\       ← this folder
rem
rem  ProjectRoot and ProjectName are resolved at runtime.
rem ============================================================

rem ── Locate devops\ and project root ─────────────────────────
set "DevOpsRoot=%~dp0"
rem Strip trailing backslash
set "DevOpsRoot=%DevOpsRoot:~0,-1%"
rem One level up → project root
for %%I in ("%DevOpsRoot%\..") do set "ProjectRoot=%%~fI"

rem ── Auto-detect project name from src\*.uproject ────────────
set "ProjectName="
for %%F in ("%ProjectRoot%\src\*.uproject") do set "ProjectName=%%~nF"
if "%ProjectName%"=="" (
    echo [config] ERROR: No .uproject file found in %ProjectRoot%\src\
    exit /b 1
)

rem ── Engine paths — edit these for your machine ──────────────
set "EnginePath_4.23=C:\Programs\UE_4.23"
set "EnginePath_5.3=C:\Programs\UE_5.3"
set "EnginePath_5.6=C:\Programs\UE_5.6"

rem Select engine version
set "SelectedEngine=%EnginePath_4.23%"

set "RunUATPath=%SelectedEngine%\Engine\Build\BatchFiles\RunUAT.bat"

rem ── Project paths (all derived automatically) ────────────────
set "ProjectFile=%ProjectName%.uproject"
set "ProjectPath=%ProjectRoot%\src\%ProjectFile%"

rem ── Configuration ────────────────────────────────────────────
set "Platform=Win32"
set "Configuration=Development"

rem ── Packaging output ─────────────────────────────────────────
set "PackagePath=%ProjectRoot%\Package"

rem ── UE Version Selector ──────────────────────────────────────
set "VersionSelector=C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe"

rem ── Target generation ────────────────────────────────────────
set "EXTRA_MODULE_NAMES=%ProjectName%"
set "TargetTemplatePath=%DevOpsRoot%\scripts\templates\GameModule.Target.cs.template"
set "TargetGameTemplatePath=%DevOpsRoot%\scripts\templates\GameOnlyModule.Target.cs.template"

rem ── Source and config paths ──────────────────────────────────
set "GameIni=%ProjectRoot%\src\Config\DefaultGame.ini"
set "SourceCodePath=%ProjectRoot%\src\Source"

rem ── Packaged executable paths ────────────────────────────────
set "ServerExePath=%PackagePath%\ServerWithClent\WindowsServer\%ProjectName%Server.exe"
set "ClientExePath=%PackagePath%\ServerWithClent\WindowsClient\%ProjectName%Client.exe"
set "GameExePath=%PackagePath%\Game\Windows\%ProjectName%.exe"

exit /b
