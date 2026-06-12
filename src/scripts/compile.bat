@echo off
echo Compiling...
erase /S /Q out\src\*
%SGDK_PATH%\bin\make -f %SGDK_PATH%\makefile.gen && start \codigo\angrydriver\out\rom.bin