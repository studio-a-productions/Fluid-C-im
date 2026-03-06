#ifndef CIM_H
#define CIM_H

#include "common_libs.h"

Cim_Status Cim_Init();
Cim_Status Cim_Quit();

typedef enum {
    CIM_INACTIVE = 0, // Cim not running/no resources allocated
    CIM_INIT, // Cim Initialized
    CIM_ACTIVE, // Cim active and updating
    CIM_PAUSED, // Cim active, but not updating
    CIM_ERROR // Cim ran into an error
} Cim_Status;

typedef enum {
    CIM_LOGTYPE_WARNING,
    CIM_LOGTYPE_ERROR,
    CIM_LOGTYPE_INFO,
    CIM_LOGTYPE_INTERNALCOMPL
} Cim_Logtype;

Cim_Status Cim_GetStatus();
void Cim_SetStatus();

void Cim_SetLogging(const bool logging);
void Cim_Log(Cim_Logtype, char*);

#endif