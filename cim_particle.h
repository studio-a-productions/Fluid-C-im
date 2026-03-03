#ifndef CIM_PARTICLE_H
#define CIM_PARTICLE_H

//#define CIM_USE_SIMD

#include "common_libs.h"
#include "cim.h"
#include "cim_math.h"
#include "cim_buffers.h"

#define CIM_PBUFFER_UPDATE_THRESHOLD 0.9F
#define CIM_PBUFFER_UPDATE_MULTIPLIER 1.3F

/*
    To safe on complexity, a particle is defined by two "types", a 
        float4 which calls contains its 2D coordinate and 2D velocity,
        and a int to represent its type which is an index to an array 
        of data. The meaning and data of this type me need not worry 
        or reason about until the "update velocity" step.


*/

/*
    ---      Particle Buffer layout      ---
    [x0, vx0, y0, vy0, x1, vx1, y1, vy1, ...]

    (this is for (future) SIMD optimization);
*/


struct Cim_ParticleBuffer {
    buffer_float4 pos_vel;
    buffer_uintt8 type; // allowing 255 types is enough for our use case
    size_t used; 
};

typedef struct { // useful for when trying to edit a single particle to gather all its data.
    float4*const fdata;
    const size_t id; // a non-zero number that should not change
} Cim_Particle;

struct Cim_ParticleBuffer* Cim_InitPBuffer(const size_t icapacity);
void Cim_UpdatePBufferPos(struct Cim_ParticleBuffer*const buffer);
void Cim_FreePBuffer(struct Cim_ParticleBuffer*const buffer);
/*
    float4 shall be x,vx,y,vy
    returns its id. Rest assured, any valid ID is not zero
*/
size_t Cim_CreateParticle(struct Cim_ParticleBuffer*const buffer, const float4 coord_vel, const int type);



#endif