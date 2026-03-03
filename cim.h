#ifndef CIM_H
#define CIM_H

#include "common_libs.h"

int Cim_Init(int pBuffSize);

int Cim_Quit();

typedef enum {
    CIM_INACTIVE, // Cim not running/no resources allocated
    CIM_INIT, // Cim Initialized
    CIM_ACTIVE, // Cim active and updating
    CIM_PAUSED, // Cim active, but not updating
    CIM_ERROR // Cim ran into an error
} Cim_Status;
typedef enum {
    CIM_ERROR_NONE, // No error
    CIM_ERROR_ERROR, // well... something went wrong?
    CIM_ERROR_PBUFFER_ALLOC, // An error happened during allocation
    CIM_ERROR_PBUFFER_INVALIDARG, // The provided argument was invalid for the Particle Buffer
    CIM_ERROR_PBUFFER_N, // Not defined error
    CIM_ERROR_INIT, // Initialization failed
    // other errors

} Cim_Error;

typedef enum {
    CIM_LOGTYPE_WARNING,
    CIM_LOGTYPE_ERROR,
    CIM_LOGTYPE_INFO,
    CIM_LOGTYPE_INTERNALCOMPL
} Cim_Logtype;

typedef enum { // temp struct, can later be actually functional
    CIM_SIMTYPE_WATER_2D,
    CIM_SIMTYPE_PHYSICS_2D,
    CIM_SIMTYPE_IDC
} Cim_SimType;

Cim_Status Cim_GetStatus();

void Cim_SetLogging(const bool logging);
void Cim_Log();

#endif