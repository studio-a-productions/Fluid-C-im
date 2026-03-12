#include <SDL.h>

#include "cim_math.h"
#include "cim_buffers.h"
#include "cim_particle.h"

#include "cim_pbehavior.h"

#include "cim_error.h"

struct Cim_ParticleBuffer* Cim_InitPBuffer(const size_t icapacity) {
    buffer_float4 tempfloat4buff = Create_Float4Buf(icapacity);
    buffer_uintt8 tempuintt8buff = Create_UIntt8Buf(icapacity);
    if (!tempfloat4buff.data || !tempuintt8buff.data) {
        if (tempfloat4buff.data) Free_Float4Buf(&tempfloat4buff);
        if (tempuintt8buff.data) Free_UIntt8Buf(&tempuintt8buff);
        Cim_AddError(CIM_ERROR_PBUFFER_ALLOC);
        return NULL;
    }
    struct Cim_ParticleBuffer* n_pbuffer = SDL_malloc(sizeof(struct Cim_ParticleBuffer));
    if (!n_pbuffer) {
        Free_Float4Buf(&tempfloat4buff);
        Free_UIntt8Buf(&tempuintt8buff);
        Cim_AddError(CIM_ERROR_PBUFFER_ALLOC);
        return NULL;
    }
    n_pbuffer->pos_vel = tempfloat4buff;
    n_pbuffer->type = tempuintt8buff;
    n_pbuffer->used = 0U;
    return n_pbuffer;
}

void Cim_FreePBuffer(struct Cim_ParticleBuffer* const buffer) {
    if (buffer->pos_vel.data) Free_Float4Buf(&buffer->pos_vel);
    if (buffer->type.data) Free_UIntt8Buf(&buffer->type);
    buffer->used = 0U;
    SDL_free(buffer);
}

uint8_t Cim_ResizePBuffer(struct Cim_ParticleBuffer* const buffer, const size_t n_s) {
    const size_t old = buffer->pos_vel.size;
    Resize_Float4Buf(&buffer->pos_vel, n_s);
    Resize_UIntt8Buf(&buffer->type, n_s);
    if ((buffer->type.size != buffer->pos_vel.size) || 
        (buffer->pos_vel.size == old)) {
        if (buffer->pos_vel.size != old) Resize_Float4Buf(&buffer->pos_vel, old);
        if (buffer->type.size != old) Resize_UIntt8Buf(&buffer->type, old);
        return (unsigned)CIM_ERROR_PBUFFER_ALLOC;
    }
    else return (unsigned)CIM_ERROR_NONE;
}

size_t Cim_CreateParticle(struct Cim_ParticleBuffer*const buffer, const float4 coord_vel, const int type) {
    if ((buffer->pos_vel.size)*CIM_PBUFFER_UPDATE_THRESHOLD <= (buffer->used))
        if (Cim_ResizePBuffer(buffer, buffer->pos_vel.size*CIM_PBUFFER_UPDATE_MULTIPLIER)) {
            Cim_AddError(CIM_ERROR_PBUFFER_ALLOC);
            return 0U;
        }
    const size_t i = buffer->used;
    Set_Float4(&buffer->pos_vel, i, coord_vel);
    Set_UIntt8(&buffer->type, i, type);
    return ++(buffer->used);
}

// ------------------------------------------------------------------------------ 


#ifdef CIM_USE_SIMD
void Cim_UpdatePBufferPos(struct Cim_ParticleBuffer*const buffer) {
    // Will be implimented >("-")>
    // not "normal" C ;-;
    return;
}
#else
void Cim_UpdatePBufferPos(struct Cim_ParticleBuffer*const buffer) {
    for (size_t i = 0U; i < buffer->pos_vel.size*4U; i += 2U)
        buffer->pos_vel.data[i] += buffer->pos_vel.data[i + 1U];
}
#endif