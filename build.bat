@echo off
call C:\Users\jaakk\esp\v5.1.6\esp-idf\export.bat
idf.py set-target esp32c3
idf.py build
pause
