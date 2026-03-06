@echo off
setlocal

:: Configuration
set SRC=cim.c cim_particle.c cim_buffers.c cim_math.c
set OBJ=cim_math.o cim_buffers.o cim_particle.o cim.o 
set SDL_DIR=SDL2
set INCLUDE=-I%SDL_DIR%/include/SDL2
set LIBS=-L%SDL_DIR%/lib -lmingw32 -lSDL2main -lSDL2
set LIB_NAME=libcim.a

echo Creating %OBJ%
gcc %INCLUDE% -c %SRC% 

echo Creating %LIB_NAME%
ar rcs %LIB_NAME% %OBJ%

endlocal

exit