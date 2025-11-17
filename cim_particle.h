#ifndef CIM_PARTICLE_H
#define CIM_PARTICLE_H

#include "common_libs.h"

struct particleBuffer {
    float* x, *y, *vx, *vy; // yes it could be a big buffer, but that's the same as an AoS
    int* type;
    int capacity, used;
};

extern struct particleBuffer cimPBuffer;

typedef struct { // useful for when trying to edit a single particle to gather all its data.
    float* x, *y, *vx, *vy; 
    int id;
} cimParticle;

// these could be function pointers, but that's besides the point
// it would require a more robust error handling system that i don't want to make
int InitCimPBuffer(int icapacity);

bool checkCimPBuffer();

int CreateCimP(float s_posx, float s_posy, float s_vx, float s_vy); // add a particle to the simPBuffer and return its ID

int FreeCimPBuffer();

#endif