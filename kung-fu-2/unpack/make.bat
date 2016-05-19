@echo off
SET PATH=C:\MinGW\bin;%PATH%
cd C:\romhacks\spartanx2\unpack
gcc -s unpack.c -o unpack.exe
pause
cls