@echo off
setlocal

:: Configuration
set SRC=main.c cim.c cim_particle.c cim_buffers.c cim_math.c
set OUT=fluidsim.exe
set SDL_DIR=SDL2
set INCLUDE=-I%SDL_DIR%/include/SDL2
set LIBS=-L%SDL_DIR%/lib -L. -lmingw32 -lSDL2main -lSDL2

echo Compiling...
:: Compile
gcc %INCLUDE% %SRC% %LIBS% -o %OUT%

echo Finished.

endlocal
exit