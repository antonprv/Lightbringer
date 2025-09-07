call "%~dp0\..\config.bat"

"%RunUATPath%" ^
BuildCookRun ^
-project="%ProjectPath%" ^
-platform=%Platform% -clientconfig=%Configuration% ^
-archivedirectory="%PackagePath%\DefaultConfig" ^
-stagingdirectory="%PackagePath%\Staging" ^
-build -cook -stage -archive -pak -package

PAUSE