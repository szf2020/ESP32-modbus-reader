@echo off
echo Cleaning build directory...
cd /d "C:\Users\jaakk\DIY projects\Microcontroller codes\ESP32 modbus reader"
C:\Users\jaakk\esp\v5.1.6\esp-idf\export.bat
idf.py fullclean
if errorlevel 1 (
    echo Clean failed
    pause
    exit /b 1
)
echo.
echo Build directory cleaned successfully.
echo Now building...
echo.
idf.py build
if errorlevel 1 (
    echo.
    echo ========================================
    echo BUILD FAILED!
    echo ========================================
    pause
    exit /b 1
)
echo.
echo ========================================
echo BUILD SUCCESSFUL!
echo ========================================
pause