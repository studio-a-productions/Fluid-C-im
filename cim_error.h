#ifndef CIM_ERROR_H
#define CIM_ERROR_H
#include "cim.h"
#include "common_libs.h"

// This file declares function prototypes that are defined in cim.c

typedef enum {
    CIM_ERROR_NONE, // No error
    CIM_ERROR_ERROR, // well... something went wrong?
    CIM_ERROR_PBUFFER_ALLOC, // An error happened during allocation
    CIM_ERROR_PBUFFER_INVALIDARG, // The provided argument was invalid for the Particle Buffer
    CIM_ERROR_PBUFFER_N, // Not defined error
    CIM_ERROR_INIT, // Initialization failed
    CIM_ERROR_EXT // External complication
    // other errors

} Cim_Error;

void Cim_AddError(const Cim_Error);
void Cim_LogError();
void Cim_DelError(); // Deletes the latest error
void Cim_DelErrorI(const int); // Deletes specific error
void Cim_DelErrors(const int*, size_t); // Deletes given an array of errors' indecies

Cim_Error Cim_GetError(); // Returns latest error
Cim_Error Cim_GetErrorI(const int); // Returns specific error
Cim_Error Cim_InvokeError(); // Gets the first error in the array and deletes it. This is a handler function, which means it expect the caller to handle this error.


#endif