#include "cim_particle.h"
#include "cim_error.h"


struct particleBuffer cimPBuffer = {NULL, NULL, NULL, NULL, NULL, 0, 0};

int Cim_InitPBuffer(int icapacity) {
    if (!icapacity || icapacity < 0) return CIM_ERROR_PBUFFER_INVALIDARG;

    cimPBuffer.x = SDL_malloc(sizeof(float) * icapacity);
    cimPBuffer.y = SDL_malloc(sizeof(float) * icapacity);
    cimPBuffer.vx = SDL_malloc(sizeof(float) * icapacity);
    cimPBuffer.vy = SDL_malloc(sizeof(float) * icapacity);
    cimPBuffer.type = SDL_malloc(sizeof(int) * icapacity);

    if (!cimPBuffer.x || !cimPBuffer.y || !cimPBuffer.vx 
        || !cimPBuffer.vy || !cimPBuffer.type)
        return CIM_ERROR_PBUFFER_ALLOC;
    cimPBuffer.capacity = icapacity;
    return CIM_ERROR_NONE;

}

int Cim_FreePBuffer() {
    if (cimPBuffer.x) SDL_free(cimPBuffer.x);
    if (cimPBuffer.y) SDL_free(cimPBuffer.y);
    if (cimPBuffer.vx) SDL_free(cimPBuffer.vx);
    if (cimPBuffer.vy) SDL_free(cimPBuffer.vy);
    if (cimPBuffer.type) SDL_free(cimPBuffer.type);

    cimPBuffer.x = cimPBuffer.y = cimPBuffer.vx = cimPBuffer.vy = NULL;
    cimPBuffer.type = NULL;
    cimPBuffer.capacity = cimPBuffer.used = 0;

    return CIM_ERROR_NONE;
}

// ------------------------------------------------------------------------------ or smth



static inline bool Cim_EnoughPBufferCap(const float threshold) {
    return ((float)cimPBuffer.used/(float)cimPBuffer.capacity) <= threshold;
}

static inline int updateFloatCimPBufferCapacity(const int *newCapacity, cimPBufferIndex buffer) {
    /*
        Yes I *COULD* add a nice for loop using pointer pointers, but who cares? (apart from style points)
    */
    float *tempBuffer = NULL;
    switch (buffer) {
        case CIM_PBUFFER_INDEX_XPOS:
            tempBuffer = SDL_realloc(cimPBuffer.x, *newCapacity);
            if (!tempBuffer) return CIM_ERROR_PBUFFER_ALLOC;
            cimPBuffer.x = tempBuffer;
            tempBuffer = NULL;
            break;
        case CIM_PBUFFER_INDEX_YPOS:
            tempBuffer = SDL_realloc(cimPBuffer.y, *newCapacity);
            if (!tempBuffer) return CIM_ERROR_PBUFFER_ALLOC;
            cimPBuffer.y = tempBuffer;
            tempBuffer = NULL;
            break;
        case CIM_PBUFFER_INDEX_XVEL:
            tempBuffer = SDL_realloc(cimPBuffer.vx, *newCapacity);
            if (!tempBuffer) return CIM_ERROR_PBUFFER_ALLOC;
            cimPBuffer.vx = tempBuffer;
            tempBuffer = NULL;
            break;
        case CIM_PBUFFER_INDEX_YVEL:
            tempBuffer = SDL_realloc(cimPBuffer.vy, *newCapacity);
            if (!tempBuffer) return CIM_ERROR_PBUFFER_ALLOC;
            cimPBuffer.vy = tempBuffer;
            tempBuffer = NULL;
            break;
        default:
            return CIM_ERROR_PBUFFER_INVALIDARG;
    }
    return CIM_ERROR_NONE;
}
static inline int updateIntCimPBufferCapacity(const int *newCapacity) {
    int* tempBuffer = SDL_realloc(cimPBuffer.type, *newCapacity);
    if (!tempBuffer) return CIM_ERROR_PBUFFER_ALLOC;

    cimPBuffer.type = tempBuffer;
    tempBuffer = NULL;

    return CIM_ERROR_NONE;
}

static inline int updateCimPBufferCap(const int *newCapacity, cimPBufferIndex buffer) {
    if (buffer == CIM_PBUFFER_INDEX_TYPE) {
        return updateIntCimPBufferCapacity(newCapacity);
    } else if (buffer == CIM_PBUFFER_INDEX_XPOS 
        || buffer == CIM_PBUFFER_INDEX_YPOS
        || buffer == CIM_PBUFFER_INDEX_XVEL 
        || buffer == CIM_PBUFFER_INDEX_YVEL) {
        return updateFloatCimPBufferCapacity(newCapacity, buffer);
    }
    else {
        return CIM_ERROR_PBUFFER_INVALIDARG;
    }
}

static inline int updateCimPBufferCapacity(const float multiplier) {
    const int newCapacity = (int)(cimPBuffer.capacity * multiplier);
    const int newFCap=newCapacity * sizeof(float);
    const int newICap=newCapacity * sizeof(int);

    Cim_AddError(updateCimPBufferCap(&newFCap, CIM_PBUFFER_INDEX_XPOS));
    Cim_AddError(updateCimPBufferCap(&newFCap, CIM_PBUFFER_INDEX_YPOS));
    Cim_AddError(updateCimPBufferCap(&newFCap, CIM_PBUFFER_INDEX_XVEL));
    Cim_AddError(updateCimPBufferCap(&newFCap, CIM_PBUFFER_INDEX_YVEL));
    Cim_AddError(updateCimPBufferCap(&newICap, CIM_PBUFFER_INDEX_TYPE));
    
    const Cim_Error cError = Cim_GetError(); // temp var checking if any failed
    if (!cError) cimPBuffer.capacity = newCapacity;
    return cError;
}

static inline int addCimP(float posx, float posy, float vx, float vy, int type) {
    if (!Cim_EnoughPBufferCap(CIM_PBUFFER_UPDATE_THRESHOLD))
        if (updateCimPBufferCapacity(CIM_PBUFFER_UPDATE_MULTIPLIER))
            return -1; // currently not handled well, but at least it's something
}

int Cim_CreateParticle(float s_posx, float s_posy, float s_vx, float s_vy, int type) {
    const int id = addCimP(s_posx, s_posy, s_vx, s_vy, type);
    if (id < 0 || id > cimPBuffer.used-1) {
        // WIP
    }
    // WIP
    return id;
}