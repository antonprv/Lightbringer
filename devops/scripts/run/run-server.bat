@echo off

call "%~dp0\..\..\config.bat"

rem start "" "%ServerExePath%" ThirdPersonExampleMap -log
start "" "%ServerExePath%" ThirdPersonExampleMap?listen -server -log -port=7777