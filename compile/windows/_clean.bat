@echo off
setlocal
:: delete without errors when no files are found
cd ..\..
del *.o 2>nul
del *.a 2>nul
endlocal
exit