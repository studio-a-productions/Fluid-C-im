#include "cim.h"
#include "common_libs.h"
#include "cim_error.h"
#include <SDL.h>

#define ERROR_ARRAY_SIZE 3 // may be changed at any time (dynamic/higher cap)

// Maybe it's time to not care about a robust error system?
static inline bool Cim_NoError(void);
typedef struct {
    Cim_Status status;
    Cim_Error error[ERROR_ARRAY_SIZE]; /* RULE: stack from "left" to "right" svp*/
    size_t s_error;
    bool log; // TREE --> LOG --> 4 PLANKS --> CRAFTING TABLE
} TypeCim;

TypeCim Cim = { CIM_INACTIVE, 
    {CIM_ERROR_NONE, CIM_ERROR_NONE, CIM_ERROR_NONE},
    true
};

static inline void Cim_SetError(const Cim_Error error, const int i) {
   Cim.error[i] = error; // we may remove the if, or not idc
}

void Cim_Log(Cim_Logtype type, const char*message) {
    SDL_LogPriority ltype;
    if (Cim.log) {
        char *pre_message = "[CIM]";
        switch (type) {
            case CIM_LOGTYPE_WARNING:
                ltype = SDL_LOG_PRIORITY_WARN;
                break;
            case CIM_LOGTYPE_ERROR:
                ltype = SDL_LOG_PRIORITY_ERROR;
                break;
            case CIM_LOGTYPE_INFO:
                ltype = SDL_LOG_PRIORITY_INFO;
                break;
            case CIM_LOGTYPE_INTERNALCOMPL:
                pre_message = "[CIM INTERNAL]";
                ltype = SDL_LOG_PRIORITY_CRITICAL;
                break;
            default: return;
        
        }
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, ltype, "%s %s", pre_message, message);
    }
}

void Cim_LogError() {
    char* desc = NULL;

    /*
    ** While we 'could' use Cim.error, 
    ** I'd much rather have a single function to change 
    ** when I decide to change the TypeCim struct.
    ** 
    ** PROVEN RIGHT after I made Cim.error an array... ha!
    */ 

    for (int i = 0; i < Cim.s_error; i++) {
        switch (Cim_GetErrorI(i)) {
            case CIM_ERROR_PBUFFER_ALLOC:
                desc = "PBuffer Allocation Failed!";
                break;
            case CIM_ERROR_PBUFFER_INVALIDARG:
                desc = "Invalid Particle (Buffer) Argument!";
                break;
            case CIM_ERROR_PBUFFER_N:
                desc = "Unknown PBuffer Error :/";
                break;
            case CIM_ERROR_INIT:
                desc = "Initializing Order Failure";
                break;
            case CIM_ERROR_ERROR:
                desc = "Error System Undefined Behavior";
                break;
            case CIM_ERROR_EXT:
                desc = "External Complication, check logs";
                break;
            default:
                desc = "No Description";
                break;
        }
        Cim_Log(CIM_LOGTYPE_ERROR, desc);
        Cim_SetError(CIM_ERROR_NONE, i);
    }
}




Cim_Status Cim_Init() {
    /*
    ** Just a generic init, though functionality may be added 
    ** later when it is needed.
    */

    if (!Cim_GetStatus()) {
        Cim_SetStatus(CIM_INIT);
    } else {
        Cim_SetStatus(CIM_ERROR);
        Cim_AddError(CIM_ERROR_ERROR);
    }
    return Cim_GetStatus();
};

Cim_Status Cim_SDLInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        Cim_SetStatus(CIM_ERROR);
        Cim_Log(CIM_LOGTYPE_INTERNALCOMPL, SDL_GetError());
        Cim_AddError(CIM_ERROR_EXT);
    }
    return Cim_GetStatus();
}

static inline void Cim_InitError() { // not needed, but who cares?
    Cim.s_error = sizeof(Cim.error)/sizeof(Cim.error[0]);
    for (int i = 0; i < Cim.s_error; i++)
        Cim_SetError(CIM_ERROR_NONE, i);   
}

Cim_Status Cim_Quit() {
    Cim_SetStatus(CIM_INACTIVE);
    return Cim_GetStatus();
}


Cim_Status Cim_GetStatus() {
    return Cim.status;
}

void Cim_SetStatus(Cim_Status status) {
    Cim.status = status;
}

static inline void Cim_UpdateErrorS() {
    Cim.s_error = sizeof(Cim.error)/sizeof(Cim.error[0]); // future proofing
}

static inline int Cim_GetErrorLastIndex() {
    if (!Cim_NoError()) 
    for (int i = Cim.s_error-1; !(i < 0); i--)
        if (Cim.error[i]) return i;
        else continue;
    else return 0; // It's better than breaking the code?
    
}
static inline bool Cim_NoError() {
    return Cim.error[0] == CIM_ERROR_NONE; 
}

Cim_Error Cim_GetError() {
    return Cim.error[Cim_GetErrorLastIndex()]; // why would you want to have an older error?
}

Cim_Error Cim_GetErrorI(const int i) {
    if (i >= (Cim.s_error)) return CIM_ERROR_ERROR;
    return Cim.error[i]; // big brain time 
}


void Cim_SetLogging(const bool logging) {
    Cim.log = logging; // log
}

void Cim_AddError(const Cim_Error error) {
    if (!error) return; 
    const int lst_indx=Cim_GetErrorLastIndex();
    if (lst_indx == Cim.s_error-1)
    if (Cim.log) Cim_Log(CIM_LOGTYPE_INFO, "Error Added");
    // Who needs '{ ... }' even?
}


static inline void Cim_CompactErrors(const int *set_arg, const int *lst_indx) { 
    /*
        A single-pass O(n) compaction algorithm that 
            can handle multiple zero-values.
        It may be advised to not call this function every frame,
            due to its nature.
        "contested" refers to the index that has been emptied and, 
            to preserve the invariable, must be refilled.
        Popular interpretations of this algorithm would use "write",
            and "read" variables, though I must say those are verbose and
            don't fit in our use-case.
        
        Kind regards,
        - 'A'
        
    */
    int contested = *set_arg;
    for (int i = contested+1; i <= *lst_indx; i++) 
        if (Cim.error[i]) {
            Cim_SetError(Cim.error[i], contested);
            Cim_SetError(CIM_ERROR_NONE, i);
            contested++;
        }
}
static inline void Cim_RemoveErrors(const int *errors, size_t amount) {
    int lowest_indx = Cim.s_error-1; 
    int last_indx = Cim_GetErrorLastIndex();
    for (int i = 0; i < amount; i++)
    {   
        if (errors[i] <= last_indx) {
            Cim.error[errors[i]] = CIM_ERROR_NONE;
            lowest_indx = errors[i] ? errors[i] < lowest_indx : lowest_indx;
        }
    }
    Cim_CompactErrors(&lowest_indx, &last_indx);
}
static inline void Cim_RemoveError(const int i) {
    const int last_indx = Cim_GetErrorLastIndex();
    if (last_indx && !Cim_NoError())
        if (i >= 0 && i < Cim.s_error && i == last_indx)
            Cim.error[i] = CIM_ERROR_NONE;
        else if (i >= 0 && i < Cim.s_error) {
            Cim.error[i] = CIM_ERROR_NONE;
            Cim_CompactErrors(&i, &last_indx);
        } else Cim_AddError(CIM_ERROR_ERROR);
    else Cim_AddError(CIM_ERROR_ERROR);
}

void Cim_DelError() { Cim.error[Cim_GetErrorLastIndex()] = CIM_ERROR_NONE; }

void Cim_DelErrorI(const int i) { Cim_RemoveError(i); } // because...?

void Cim_DelErrors(const int*errArray, size_t s_errArray) { Cim_RemoveErrors(errArray, s_errArray); }

Cim_Error Cim_InvokeError() {
    if (!Cim_NoError()) {
        const Cim_Error first_err = Cim_GetErrorI(0);
        Cim_DelErrorI(0);
        return first_err;
    } else return CIM_ERROR_NONE;
}