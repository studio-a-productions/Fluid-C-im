# Invariables

## Exp

This codebase relies on several invariants that are required for each function. None should break these invariants and it's up to the caller to ensure no undefined behavior arises. This file is a place to quickly find these invariants.

## Quick Overview

Here's a quick overview of all invariants per API.

### Cim API

- `Cim.error` is left-packed, no holes.
- `CIM_ERROR_NONE` == 0 
- `Cim_GetError()` returns last error
- `Cim_Status` updates correctly
- `Cim_PBuffer ID` != 0
- `CIM_USE_SIMD` shall be defined 
- `const` use

### App API

- currently `NULL`

## Cim Invariants

### Cim.error array

Whether an array or a pointer, this variable of the TypeCim struct should always start at index 0 and have no zeros between non-zero ellements.

### CIM_ERROR_NONE

This error code doesn't stand for an error, rather it stands for the absence of one, and thus logically it is zero (or NULL). Must the Cim_Error enum be changed, CIM_ERROR_NONE must remain zero, either expressed or implied by the structure.

### Cim_GetError()

All functional logic expect the latest error to be at the most right index. Because in most cases, you'd like to know what last happened, `GetError()` returns the latest error. Do not mistake this for a future `InvokeError()` function, which may or may not give the first error and delete it.

### Cim_Status

The simulation's status is important, update logic will depend on this heavily, so instead of asking if there's an error, the update can get the current status. If any event or interupt happens, make sure Cim_Status in Cim.status is updated correctly.

### Cim_ParticleBuffer ID

A particle's identity is linked to the amount of particles used, which ensure that the identity of a unsigned zero will is analogue to an error, so any particle creation check can be used as an if statement. 

### CIM_USE_SIMD

This is a macro "flag" that the user shall define or undefine depending on their needs. If defined, functions like `Cim_PBufferUpdatePos()` shall use their `_SIMDImpl` over the `_SimplImpl`. This does not care about the `PLATFORM` flag.

### Const "Over"use

Whether internal and private, or external and public, any function shall declare whether an input variable is `const`. This is to help the compiler optimise these functions and variables, sometimes even pre-computing parts. This is also a matter of discipline.