call "%~dp0\..\..\config.bat"

setlocal enabledelayedexpansion

set Key=CopyrightNotice
set Value=

for /f "usebackq tokens=1,* delims==" %%A in (`findstr /b "%Key%=" "%GameIni%"`) do (
    set Value=%%B
)

endlocal & set CopyrightNotice=// %Value%

exit /b
