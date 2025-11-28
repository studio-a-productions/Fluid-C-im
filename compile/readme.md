# use

to use, it's very simple, just run (from the root folder)

on unix:

```bash

./compile/unix/... # here goes your call

```

on windows:

```batch

.\compile\windows\...

```

# calls

you can call:
- `main` for your source file*s* (eg. main.c; this requires the libraries to be compiled already)
- `libs` for compiling *both* cim **and** app
- `cim` for *only* compiling the *cim* library
- `app` for *only* compiling the *app* library
- `clean` deletes all object and library files in the root folder
- `cleana` deletes all files created (even the executable)

(all `.bat` or `.sh`)

> do not call the underscore files, they're helpers.

# updating

## for source

only edit the main.* files (**windows *and* unix**)

## for libraries

edit **both** app.\* and cim.\*, but also their helper variants (`_cim.*` *and* `_app.*` not `_clean.*` *or other cleanup functions* unless you are creating other stuff (like directories for compiled assets for example))d
