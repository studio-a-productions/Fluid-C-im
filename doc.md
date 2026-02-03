# Fluid-C-im Documentation

## outdated!!!

This is outdated, focussing on dev. Things here will change.

## Naming Convention

### Variables

In general, variables are short, taking the *first* **3 letters** of the variable (eg. `win` *for window*).

Some variables may start with `s_` (`S_ for macros`), which usually translates to *size* or *size of*. If it ands with `_s` or `_S` it usually just means `...'s size`, but can also be an alternative to *size of* or *size*.

Macros and constants are usually in full caps, just as most C projects.

### Functions

This project uses a naming convention for (*public*) functions like that of SDL, starting with `lib_` and using **upercase** between words. Internal *private* functions may sometimes not follow this rule, because why not?

## Rules

## invariables

READ `invariables.md` FOR SPECIFICS!

### Returns

Function that could possibly fail are almost always `int`s, and any `non-zero` number should be returned for failure. This is not *Rust*, so you need to keep track of your resources.

## Cim API

### Public

```c

void Cim_Init(int pBuffSize); // Initializes buffers, returns non-zero upon failure

void Cim_Quit(); // Closes all resources

Cim_Status Cim_GetStatus(); // Returns the current status
// There's no Cim_GetError() unless you include cim_error.h

typedef enum { // Status type
    CIM_INACTIVE, // Cim not running/no resources allocated
    CIM_INIT, // Cim Initialized
    CIM_ACTIVE, // Cim active, updating
    CIM_PAUSED, // Cim active, not updating
    CIM_ERROR // Cim ran into an error, pauzed
} Cim_Status;

typedef enum {
    CIM_ERROR_NONE, // No error, "succes"
    CIM_ERROR_ERROR, // Undefined error
    CIM_ERROR_PBUFFER_ALLOC, // Alloc error within the Particle Buffer
    CIM_ERROR_PBUFFER_INVALIDARG, // The provided argument was invalid for the Particle Buffer
    CIM_ERROR_PBUFFER_N, // Not defined Particle Buffer error
    CIM_ERROR_INIT, // Initialization failed
} Cim_Error;

```

### Private

```c

// WIP

```

### PLANNED

* add/get particle function
* simulation stuff
* (*possibly*) a function to add resources or render sprites.
* a macro to remove parts of the error logging in compile-time

## App API

### Public 

```c

struct AppStruct { // App struct to contain pointers to window and renderer, not needed outside (currently)
    SDL_Window* win;
    SDL_Renderer* rend;
    bool running;
};

extern struct AppStruct App; // the only App we need (why would you want two apps in one app?)

int AppInit(const int width, const int height); // create the window and renderer with (initial) width and height
void AppUpdate(); // update the window and handle input
int AppQuit(); // Quit app, destroy window and free resource buffers

```

### Private 

`RENDER_H` is still WIP. 

### PLANNED

* buffer for objects to render
* texture buffer/atlas
* automatic scaling
* settings