@echo off

call "%~dp0\..\..\config.bat"

call "%~dp0\..\templates\generate-copyright.bat"

set TARGET_TYPE=Server
set MODULE_NAME=%ProjectName%
set TargetFileName=%MODULE_NAME%%TARGET_TYPE%.Target.cs
set TargetFilePath=%SourceCodePath%\%TargetFileName%

call "%~dp0\_create-target.bat"