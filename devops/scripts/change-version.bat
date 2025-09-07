@echo off

call "%~dp0\..\config.bat"

"%VersionSelector%" -switchversionsilent "%ProjectPath%" "%SelectedEngine%"

PAUSE