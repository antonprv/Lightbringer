@echo off

call "%~dp0\..\..\config.bat"

call "%~dp0\..\templates\generate-copyright.bat"

set TARGET_TYPE=Game
set MODULE_NAME=%ProjectName%
set TargetFileName=%MODULE_NAME%.Target.cs
set TargetFilePath=%SourceCodePath%\%TargetFileName%

call "%~dp0\_create-game-target.bat"