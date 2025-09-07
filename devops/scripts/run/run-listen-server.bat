@echo off

call "%~dp0\..\..\config.bat"

start "" "%GameExePath%" ?listen -WINDOWED -ResX=600 -ResY600 -WinX=1230 -WinY=50 -server -log -port=7777