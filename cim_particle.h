#ifndef CIM_PARTICLE_H
#define CIM_PARTICLE_H

#include "common_libs.h"

#define CIM_PBUFFER_UPDATE_THRESHOLD 0.9F
#define CIM_PBUFFER_UPDATE_MULTIPLIER 1.3F

struct particleBuffer {
    float* x, *y, *vx, *vy; // yes it could be a big buffer, but that's the same as an AoS
    int* type;
    int capacity, used;
};

extern struct particleBuffer cimPBuffer;

typedef struct { // useful for when trying to edit a single particle to gather all its data.
    float *x, *y, *vx, *vy; 
    int id;
} cimParticle;

typedef enum { // all buffer indexes for the Cim particle buffer
    CIM_PBUFFER_INDEX_XPOS,
    CIM_PBUFFER_INDEX_YPOS,
    CIM_PBUFFER_INDEX_XVEL,
    CIM_PBUFFER_INDEX_YVEL,
    CIM_PBUFFER_INDEX_TYPE
} cimPBufferIndex;

int InitCimPBuffer(int icapacity);

int CheckCimPBuffer();

int CreateCimP(float s_posx, float s_posy, float s_vx, float s_vy, int type); // add a particle to the simPBuffer and return its ID

int FreeCimPBuffer();

#endif