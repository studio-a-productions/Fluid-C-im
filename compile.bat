@echo off
setlocal

:: Configuration
set SRC=main.c
set OUT=fluidsim.exe
set SDL_DIR=SDL2
set INCLUDE=-I%SDL_DIR%/include/SDL2
set LIBS=-L%SDL_DIR%/lib -lmingw32 -lSDL2main -lSDL2

:: Compile
gcc %INCLUDE% %SRC% %LIBS% -o %OUT%

:: Run
%OUT%
