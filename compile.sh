#!/bin/bash

# Configuration
SRC="app.c main.c"
OUT="fluidsim"
CFLAGS="$(sdl2-config --cflags)"
LIBS="$(sdl2-config --libs)"

# Compile
gcc $CFLAGS $SRC $LIBS -o $OUT

# Run
./$OUT
