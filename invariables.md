# Invariants

## Exp

This codebase relies on several invariants that are required for each function. None using the APIs listed should break these invariants and it's up to the caller to ensure no undefined behavior arises. This file is a place to quickly find these invariants.

We may sometimes use "invariable" to refer to an invariant, just because we can.

## Quick Overview

Here's a quick overview of all invariants per API.

### Cim API

- `Cim.error` is left-packed, no holes
- `CIM_ERROR_NONE` == 0 
- `Cim_GetError()` returns last error
- `Cim_InvokeError()` *don't*
- `Cim_Status` updates correctly
- `Cim.error` is updated after `Cim.status`
- `Cim_PBuffer ID` != 0
- `CIM_USE_SIMD` shall be defined 
- `const` use
- `SDL.h` no public-incl

### App API

- currently `NULL`

### Other

- use `beter_bool.h`

## Cim Invariants

### Cim.error array

Whether an array or a pointer, this variable of the TypeCim struct should always start at index 0 and have no zeros between non-zero elements.

### CIM_ERROR_NONE

This error code doesn't stand for an error, rather it stands for the absence of one, and thus logically it is zero (or NULL). Must the Cim_Error enum be changed, CIM_ERROR_NONE must remain zero, either expressed or implied by the structure.

### Cim_GetError()

All functional logic expect the latest error to be at the most right index, because in most cases, you'd want to know what last happened, `GetError()` returns the latest error. Do not mistake this for a future `InvokeError()` function, which may or may not give the first error and delete it.

### Cim_InvokeError()

For those who want to handle the oldest error, you can use `InvokeError()` to return the first error of Cim.errors, though you should be aware that it runs an O(n) single-pass compaction algorithm and thus you shouldn't use this for handling errors from old to new, and instead use a for loop like Cim_LogError() does:
```c
for (unsigned int i=0U;i<max; i++) {
    Cim_Error cerror = Cim_GetErrorI(i);
    switch (cerror) {
        case ...
    }
    // do stuff
}

```

### Cim_Status

The simulation's status is important, update logic will depend on this heavily, so instead of asking if there's an error, the update can get the current status. If any event or interrupt happens, make sure Cim_Status in Cim.status is updated correctly.

### Cim Err Order

While technically there isn't any assumption (yet) using this invariant, it is a matter of courtesy to update a status before adding the error to the buffer, as there's no problem with knowing there was an error without it being specified, though knowing there is an error and not handling it is much worse. 

A later reasoning for the Cim Error Order would be that the system could handle resources by itself without having a public entity or caller handle those, though that sounds disgustingly close to Python-style languages.

### Cim_ParticleBuffer ID

A particle's identity is linked to the amount of particles used, which ensure that the identity of a unsigned zero will always be analogous to an error, and thus any particle creation call can be utilised as a check inside an if statement.

### CIM_USE_SIMD

This is a macro "flag" that the user shall define or undefine depending on their needs. If defined, functions like `Cim_PBufferUpdatePos()` shall use their `_SIMDImpl` over the `_SimplImpl`. This does not care about the `PLATFORM` flag.

### Const "Over"use

Whether internal and private, or external and public, any function shall declare whether an input variable is `const`. This is to help the compiler optimise these functions and variables, sometimes even pre-computing parts. This is also a matter of discipline.

### No Public SDL Includes

As for the reason, thou mayest ask the *GCC Gods*, because including `SDL2`'s header within the Cim API has resulted in their rage. Whether by smiting compiler with typedef errors that are untruthful, or giving a false build that shall fail upon launch, they taught us that `SDL.h` shall result in unrelated problems.

> If it works, don't fix it.

## App Invariants

### NULL

not yet, be patient

## Other

### Beter Bool

A normal bool, depending on stdbool, can just be a full int32_t, but let's be honest, who needs anything else than true and false for a bool? That's why bbool is a `uint8_t` and both btrue and bfalse are defined as:
```c
#define btrue  ((bbool)1U)
#define bfalse ((bbool)0U)
``` 
Though this would be even better if modern systems allowed Sub-Byte memory \\\'\_\'\/