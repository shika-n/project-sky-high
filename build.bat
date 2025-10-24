@echo off
echo "================ BUILDING ==============="
cd build\Release && ninja

if not %ERRORLEVEL% == 0 (
	goto exit
)

if "%1" == "run" (
	echo "================ RUNNING ================"
	SkyHigh.exe
)

:exit
cd ..\..
