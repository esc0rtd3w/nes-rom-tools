@echo off
SET PATH=C:\MinGW\bin;%PATH%
cd C:\romhacks\spartanx2\repack
gcc -s repack.c -o repack.exe
pause
cls