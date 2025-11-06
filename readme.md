# Disclaimer

This project is just a small scale fluid simulator that will be written in C using SDL2 (2.32.10) and compiled using GCC during development, follow the `Build Guide` to build the project.

This project is under the MIT license, and SDL2 (which it uses) is under the zlib license, all files in the SDL2 folder are (Currently) part of the SDL 2.32.10 MinGW32 bundle.

# Fluid-C-im

## Project Overview

**Fluid-C-im** will be a small interactive fluid simulator in C, currently using only `SDL2 and C`.

Later, I *might* add `OpenGL` and/or `cimgui`, which might make development easier, but isn't currently planned.

This is just a project for fun, but feel free to use any part of the code for your own project!

### Project Goals

The goals for this project are to:

- achieve *interactive* fluid simulation

- learn about *2D rendering* and underlying techniques

- achieve GUI *without external libraries*

- run at 60 fps

### Project Dependencies

#### Current

Currently, we *only* use SDL2 and the C standard library. This is to have the most control over every aspect of the application and project without delving into platform specific APIs (win32 flashbacks...)

#### Future

If this project expands, for example becoming a small game, it would eventually need more GPU related stuff, which would need at least OpenGL to keep it cross-platform. 

The project will avoid using `C++ libraries` (because C is based), already established `frameworks` for stuff like *physics and rendering*, and *other languages* (no cross-language stuff).

## Build Guide

### Windows

#### GCC

For those using GCC (`MinGW32`), they should be able to use the project as is, as all libraries are already in the project.

Just run `compile.bat` or run the command yourself, *compile.bat* is just a quick way to compile and run during development.

#### Visual Studio

You can compile the project in **Visual Studio**, though it will be seen as a `C++ project`. 

Download the `Win32` package. This project uses [SDL2 2.32.10](https://github.com/libsdl-org/SDL/releases/tag/release-2.32.10). You are free to use your SDL version of choice, though compatibility may vary.

In the settings, you should set it to `Compile as C`. This C code should be compatible even with the C standard set to legacy.

### Unix

Follow the [SDL2 Unix Installation Guide](https://wiki.libsdl.org/SDL2/Installation#linuxunix) for your system, the `compile.sh` script expects Ubuntu, so changes might need to be made for your system.

### Other 

For other platforms, you'll need to search on the [rest of the SDL2 Installation Guide](https://wiki.libsdl.org/SDL2/Installation) and may need to create your own compile/build script if necessary.

## Use for Educational Purposes

Feel free to use this project for *educational purposes*. Most of the code is uncommented because it's straight forward in what it does. Though you're free to add or remove comments when using the current, past or future versions of this project.

Of course, a lot of people start out with high-level languages like '`Python`', though this project might be useful for showing the underlying work or can be used as a starting point or reference for those who want to use a low-level language like C.

Do not take any part of this code as top-tier, I myself am not a senior dev at all and am still learning parts of C!