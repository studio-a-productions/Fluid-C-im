@echo off
setlocal

:: Configuration
set SRC=app.c app_render.c app_assets.c
set OBJ=app.o
set SDL_DIR=SDL2
set INCLUDE=-I%SDL_DIR%/include/SDL2
set LIBS=-L%SDL_DIR%/lib -lmingw32 -lSDL2main -lSDL2
set LIB_NAME=libapp.a

cd ..\..

echo Creating %OBJ%
gcc %INCLUDE% -c %SRC% 

echo Creating %LIB_NAME%
ar rcs %LIB_NAME% %OBJ%

endlocal

exit
