@echo off
setlocal

cd .\compile\windows\

echo Starting up compile chain...
start _cim.bat
start _app.bat

endlocal

exit