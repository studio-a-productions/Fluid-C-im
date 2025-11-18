@echo off
setlocal

:: Configuration
set SRC=cim_particle.c cim.c app.c main.c
set OUT=fluidsim.exe
set SDL_DIR=SDL2
set INCLUDE=-I%SDL_DIR%/include/SDL2
set LIBS=-L%SDL_DIR%/lib -lmingw32 -lSDL2main -lSDL2

echo Compiling...
:: Compile
gcc %INCLUDE% %SRC% %LIBS% -o %OUT%

Echo Running %out%
:: Run
%OUT%
