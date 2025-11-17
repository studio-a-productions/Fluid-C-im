# Fluid-C-im Documentation

## Naming Convention

### Variables

In general, variables are short, taking the *first* **3 letters** of the variable (eg. `win` *for window*).

Some variables may start with `s_` (`S_ for macros`), which usually translates to *size* or *size of*. 

Macros and constants are usually in full caps, just as most C projects.

### Functions

For public functions (exposed to `main.c`), usually it starts with the name of the API or library and then what the function does (eg. `CimInit`).

`Init` for startup, `Quit` for freeing and quiting.

## Rules

### Returns

Function that could possibly fail are almost always `int`s, and any `non-zero` number should be returned for failure. This is not *Rust*, so you need to keep track of your resources.

## Cim API

### Public

```c

int CimInit(int pBufferSize); // Initialize all CIM components, does not include APP related stuff.

int CimQuit(); // Free resources

```

### Private

```c

struct particleBuffer { // SoA (stuct of arrays)
    float* x, *y, *vx, *vy; // these are the buffers for position (x, y) and velocity (vx, vy)
    int* type; // array of types, each particle can be part of the type table, which will hold information like mass
    int capacity, used; // buffer indicators, current capacity and how much is used up.
};

int InitCimPBuffer(const int size); // This function will allocate the initial buffer and checks if something went wrong.
int FreeCimPBuffer(); // Frees the memory of the initialized arrays (checks for each one)

```