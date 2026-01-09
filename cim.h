#ifndef CIM_H
#define CIM_H

int CimInit(int pBuffSize);

int CimQuit();
typedef enum {
    CIM_UNINIT,
    CIM_INIT,
    CIM_ACTIVE,
    CIM_UNACTIVE,
    CIM_PAUSED,
    CIM_ERROR
} cimStatus;

#endif