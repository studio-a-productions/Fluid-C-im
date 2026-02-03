#include "cim.h"
#include "cim_error.h"
#include "cim_particle.h"
#include "common_libs.h"

#define ERROR_ARRAY_SIZE 3 // may be changed at any time (dynamic/higher cap)

// Maybe it's time to not care about a robust error system?

typedef struct {
    Cim_Status status;
    Cim_Error error[ERROR_ARRAY_SIZE]; /* RULE: stack from "left" to "right" svp*/
    size_t s_error;
    bool log; // TREE --> LOG --> 4 PLANKS --> CRAFTING TABLE
} TypeCim;

TypeCim Cim = { CIM_INACTIVE, 
    {CIM_ERROR_NONE, CIM_ERROR_NONE, CIM_ERROR_NONE},
    true};

void Cim_Log(Cim_Logtype type, char*message) {
    if (Cim.log) {
        char *pre_message = NULL;
        switch (type) {
            case CIM_LOGTYPE_WARNING:
                pre_message = "[WARNING] Cim";
                break;
            case CIM_LOGTYPE_ERROR:
                pre_message = "[ERROR] Cim";
                break;
            case CIM_LOGTYPE_INFO:
                pre_message = "[INFO] Cim";
                break;
            case CIM_LOGTYPE_INTERNALCOMPL:
                pre_message = "[COMPLICATION] Cim";
                break;
            default: return;
        
        }
        SDL_Log("%s: %s\n", pre_message, message);
    }
}

void Cim_LogError() {
    const char* desc = NULL;

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
            case CIM_ERROR_NONE:
                return;
            default:
                desc = "No Description";
                break;
        }
        Cim_Log(CIM_LOGTYPE_ERROR, desc);
    }
}

int Cim_Init(int pBuffSize) {
    /*
    ** Note: update this with the new improved error system
    */
    // Please note your own ass, thank you!
    Cim_InitError();

    Cim_AddError(Cim_InitPBuffer(pBuffSize));
    if (Cim_GetError()) {
        if (Cim.log) Cim_LogError();
        return CIM_ERROR;
    }
    
    Cim.status = CIM_INIT; // no way... really?
    return CIM_INIT;
};

static inline void Cim_InitError() { // not needed, but who cares?
    Cim.s_error = sizeof(Cim.error)/sizeof(Cim.error[0]);
    for (int i = 0; i < Cim.s_error; i++)
        Cim_SetError(CIM_ERROR_NONE, i);   
}

int Cim_Quit() {
    Cim.status = CIM_ERROR ? Cim_FreePBuffer() : CIM_INACTIVE; // remember to update this to an "if" when more functions are added
    return Cim_GetStatus();
}


Cim_Status Cim_GetStatus() {
    return Cim.status;
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

static inline void Cim_SetError(const Cim_Error error, const int i) {
   Cim.error[i] = error; // we may remove the if, or not idc
   if (Cim.log) Cim_Log(CIM_LOGTYPE_INFO, "Error Set");
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