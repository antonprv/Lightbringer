@echo off

call "%~dp0\..\..\config.bat"

"%RunUATPath%" BuildCookRun ^
-project="%ProjectPath%" ^
-platform=%Platform% ^
-archivedirectory="%PackagePath%\ServerWithClent" ^
-clientconfig="%Configuration%" ^
-serverconfig="%Configuration%" ^
-build -cook -iterate -package -stage -archive -pak -allmaps -iostore -compressed -server -client

pause