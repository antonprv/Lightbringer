setlocal enabledelayedexpansion
if exist "%TargetFilePath%" del /q "%TargetFilePath%"

for /f "usebackq delims=" %%a in ("%TargetTemplatePath%") do (
	set "line=%%a"
	:: Replace placeholders with actual values
	set "line=!line:%%MODULE_NAME%%=%MODULE_NAME%!"
	set "line=!line:%%TARGET_TYPE%%=%TARGET_TYPE%!"
	set "line=!line:%%EXTRA_MODULE_NAMES%%=%EXTRA_MODULE_NAMES%!"
	set "line=!line:%%COPYRIGHT_LINE%%=%CopyrightNotice%!"
	echo !line! >> "%TargetFilePath%"

)

endlocal

call python "%~dp0\_format-file.py" "%SourceCodePath%"