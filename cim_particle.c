#include "cim_particle.h"


struct particleBuffer cimPBuffer = {NULL, NULL, NULL, NULL, NULL, 0, 0};

int InitCimPBuffer(int icapacity) {
    if (!icapacity) {
        SDL_Log("InitCimBuffer Error: no initial capacity given.\n");
        return -1;
    }
    else if (icapacity < 0) {
        SDL_Log("InitCimPBuffer Error: a buffer capacity cannot be negative.\n");
        return -1;
    }
    cimPBuffer.x = SDL_malloc(sizeof(float) * icapacity);
    if (!cimPBuffer.x) {
        SDL_Log("InitCimPBuffer Error w/ x-pos buffer.\n");
        return -1;
    }
    cimPBuffer.y = SDL_malloc(sizeof(float) * icapacity);
    if (!cimPBuffer.y) {
        SDL_Log("InitCimPBuffer Error w/ y-pos buffer.\n");
        return -1;
    }
    cimPBuffer.vx = SDL_malloc(sizeof(float) * icapacity);
    if (!cimPBuffer.vx) {
        SDL_Log("InitCimPBuffer Error w/ x-veloc buffer.\n");
        return -1;
    }
    cimPBuffer.vy = SDL_malloc(sizeof(float) * icapacity);
    if (!cimPBuffer.vy) {
        SDL_Log("InitCimPBuffer Error w/ y-veloc buffer.\n");
        return -1;
    }
    cimPBuffer.type = SDL_malloc(sizeof(int) * icapacity);
    if (!cimPBuffer.type) {
        SDL_Log("InitCimPBuffer Error w/ y-veloc buffer.\n");
        return -1;
    }
    cimPBuffer.capacity = icapacity;
    return 0;

}

int FreeCimPBuffer() {
    if (cimPBuffer.x) SDL_free(cimPBuffer.x);
    if (cimPBuffer.y) SDL_free(cimPBuffer.y);
    if (cimPBuffer.vx) SDL_free(cimPBuffer.vx);
    if (cimPBuffer.vy) SDL_free(cimPBuffer.vy);
    if (cimPBuffer.type) SDL_free(cimPBuffer.type);

    cimPBuffer.x = cimPBuffer.y = cimPBuffer.vx = cimPBuffer.vy = NULL;
    cimPBuffer.type = NULL;
    cimPBuffer.capacity = cimPBuffer.used = 0;

    return 0;
}

// ------------------------------------------------------------------------------ or smth



static inline bool enoughCimPBufferCapacity(const float threshold) {
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
            if (!tempBuffer) return -1;
            cimPBuffer.x = tempBuffer;
            tempBuffer = NULL;
            break;
        case CIM_PBUFFER_INDEX_YPOS:
            tempBuffer = SDL_realloc(cimPBuffer.y, *newCapacity);
            if (!tempBuffer) return -1;
            cimPBuffer.y = tempBuffer;
            tempBuffer = NULL;
            break;
        case CIM_PBUFFER_INDEX_XVEL:
            tempBuffer = SDL_realloc(cimPBuffer.vx, *newCapacity);
            if (!tempBuffer) return -1;
            cimPBuffer.vx = tempBuffer;
            tempBuffer = NULL;
            break;
        case CIM_PBUFFER_INDEX_YVEL:
            tempBuffer = SDL_realloc(cimPBuffer.vy, *newCapacity);
            if (!tempBuffer) return -1;
            cimPBuffer.vy = tempBuffer;
            tempBuffer = NULL;
            break;
        default:
            return -1;
    }
    return 0;
}
static inline int updateIntCimPBufferCapacity(const int *newCapacity) {
    int* tempBuffer = SDL_realloc(cimPBuffer.type, *newCapacity);
    if (!tempBuffer) return -1;

    cimPBuffer.type = tempBuffer;
    tempBuffer = NULL;

    return 0;
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
        SDL_Log("CimPBuffer Realloc failed: invalid buffer index");
        return -1;
    }
}

static inline int updateCimPBufferCapacity(const float multiplier) {
    const int newCapacity = (int)(cimPBuffer.capacity * multiplier);
    const int newFCap=newCapacity * sizeof(float);
    const int newICap=newCapacity * sizeof(int);

    if (updateCimPBufferCap(&newFCap, CIM_PBUFFER_INDEX_XPOS)) return -1;
    if (updateCimPBufferCap(&newFCap, CIM_PBUFFER_INDEX_YPOS)) return -1;
    if (updateCimPBufferCap(&newFCap, CIM_PBUFFER_INDEX_XVEL)) return -1;
    if (updateCimPBufferCap(&newFCap, CIM_PBUFFER_INDEX_YVEL)) return -1;
    if (updateCimPBufferCap(&newICap, CIM_PBUFFER_INDEX_TYPE)) return -1;

    cimPBuffer.capacity = newCapacity;
    return 0;
    
}

static inline int addCimP(float posx, float posy, float vx, float vy, int type) {
    if (!enoughCimPBufferCapacity(CIM_PBUFFER_UPDATE_THRESHOLD))
    if (updateCimPBufferCapacity(CIM_PBUFFER_UPDATE_MULTIPLIER))
    {
        SDL_Log("Cim Error w/ realloc PBuffers.\n");
        return -1;
    };



    
}

int CreateCimP(float s_posx, float s_posy, float s_vx, float s_vy, int type) {
    const int id = addCimP(s_posx, s_posy, s_vx, s_vy, type);
    if (id < 0) {
        // error happened
    }

    return id;
}