#ifndef CIM_ERROR_H
#define CIM_ERROR_H
#include "cim.h"
#include "common_libs.h"

// This file declares function prototypes that are defined in cim.c

void Cim_AddError(const Cim_Error);
void Cim_LogError();
void Cim_DelError(); // Deletes the latest error
void Cim_DelErrorI(const int); // Deletes specific error
void Cim_DelErrors(const int*, size_t); // Deletes given an array of errors' indecies

Cim_Error Cim_GetError(); // Returns latest error
Cim_Error Cim_GetErrorI(const int); // Returns specific error
Cim_Error Cim_InvokeError(); // Gets the first error in the array and deletes it. This is a handler function, which means it expect the caller to handle this error.


#endif