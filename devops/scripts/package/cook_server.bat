@echo off

call "%~dp0\..\..\config.bat"

"%RunUATPath%" BuildCookRun ^
-project="%ProjectPath%" ^
-platform=%Platform% ^
-serverconfig="%Configuration%" ^
-build -cook -iterate -skippackage -allmaps -server -noclient