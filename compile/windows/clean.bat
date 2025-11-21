@echo off
setlocal
:: delete without errors when no files are found
del *.o 2>nul
del *.a 2>nul
endlocal
exit