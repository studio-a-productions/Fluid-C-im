@echo off
setlocal
:: delete without errors when no files are found
del *.exe 2>nul
cd .\compile\windows\
call _clean.bat

echo All cleaned up!
endlocal
exit