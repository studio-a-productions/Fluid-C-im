# Disclaimer

This project is just a small scale fluid simulator that will be written in C using SDL2 (2.32.10) and compiled using GCC during development, follow the `Build Guide` to build the project.

# Fluid-C-im

## Project Overview

**Fluid-C-im** will be a small interactive fluid simulator in C, currently using only SDL2 and C.

Later, I might add `OpenGL` and/or `cimgui`, which might make development easier.

This is just a project for fun, but feel free to use any part of the code for your own project!

## Build Guide

### Windows

#### GCC

For those using GCC (`MinGW32`), they should be able to use the project as is, as all libraries are already in the project.

Just run `compile.bat` or run the command yourself, *compile.bat* is just a quick way to compile and run during development.

#### Visual Studio

You can compile the project in Visual Studio, though it will be seen as a "C++" project. 

Download the `Win32` package. This project uses [SDL2 2.32.10](https://github.com/libsdl-org/SDL/releases/tag/release-2.32.10). You are free to use your SDL version of choice, though compatibility may vary.

In the settings, you should set it to `Compile as C`. This C code should be compatible even with the C standard set to legacy.

### Unix

Follow the [SDL2 Unix Installation Guide](https://wiki.libsdl.org/SDL2/Installation#linuxunix) for your system, the compile.sh script expects Ubuntu, so changes might need to be made for your system.

### Other 

For other platforms, you'll need to search on the [rest of the SDL2 Installation Guide](https://wiki.libsdl.org/SDL2/Installation) and may need to create your own compile/build script if necessary.