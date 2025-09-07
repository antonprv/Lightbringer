@echo off

call "%~dp0\..\..\config.bat"

"%RunUATPath%" BuildCookRun ^
-project="%ProjectPath%" ^
-platform=%Platform% ^
-clientconfig="%Configuration%" ^
-build -cook -iterate -skippackage -allmaps -client