#ifndef CIM_ENVIRONMENT_H

#ifdef __cplusplus
#error Cim is not compatible with C++
#endif

#define MODERN_SYS 11
#define RETRO_SYS 98
#define DEBUGING_INC 7 // holy for the undeserving
#define CHECKS_INC 6 // in bound checks (devil's number)
// optional but... maybe we do #ifdef (expr) ||/&& (expr) instead of...
/*
** More options can be added here, but make sure there are flags for the combinations you allow
*/
#define DEBUG_INC_CHECK_INC 1 // logs all and if (in bounds) checks


// settings -----------------------------

#define COMPILE_FLAGS DEBUG_INC_CHECK_INC
#define PLATFORM RETRO_SYS

#endif
