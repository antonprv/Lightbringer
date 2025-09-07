@echo off

rem Engine params
set EnginePath_4.23=C:\Programs\UE_4.23
set EnginePath_5.3=C:\Programs\UE_5.3
set EnginePath_5.6=C:\Programs\UE_5.6

rem Select engine from the list
set SelectedEngine=%EnginePath_4.23%

rem !! Engine version for packaging !!
set RunUATPath=%SelectedEngine%\Engine\Build\BatchFiles\RunUAT.bat

rem Project params
set ProjectRoot=d:\Projects\Lightbringer
set ProjectName=Lightbringer
set ProjectFile=%ProjectName%.uproject
set ProjectPath=%ProjectRoot%\%ProjectFile%

rem Configuration params
set Platform=Win32
set Configuration=Development

rem Packaging params
set PackagePath=%ProjectRoot%\Package

rem Build Visual Studio Project files and change version
set VersionSelector=C:\Program Files (x86)\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe

rem Target params
set EXTRA_MODULE_NAMES=%ProjectName%

set TargetTemplatePath=D:\Projects\Lightbringer\devops\scripts\templates\GameModule.Target.cs.template

set TargetGameTemplatePath=D:\Projects\Lightbringer\devops\scripts\templates\GameOnlyModule.Target.cs.template

set GameIni=d:\Projects\Lightbringer\Config\DefaultGame.ini

set SourceCodePath=D:\Projects\Lightbringer\Source


rem Run client and server
set ServerExePath=%ProjectRoot%\Package\ServerWithClent\WindowsServer\%ProjectName%Server.exe
set ClientExePath=%ProjectRoot%\Package\ServerWithClent\WindowsClient\%ProjectName%Client.exe
set GameExePath=%ProjectRoot%\Package\Game\Windows\%ProjectName%.exe

exit /b