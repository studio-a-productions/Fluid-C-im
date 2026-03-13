#include "cim.h"
#include "cim_particle.h"

// initial window size
// we're doing a 8:6/4:3 ratio to match the CANVAS
#define W_W 800U
#define W_H 600U
// canvas size (upscale 4)
#define CANVAS_W 200U
#define CANVAS_H 150U

#define PARTICLE_BUFFER_S 100U


int main() {
    if (!Cim_Init()) return 1;
    Cim_SetLogging(true);
    
    Cim_Log(CIM_LOGTYPE_INFO, "hello world!");
    
    
    if (Cim_Quit()) return 1;
    return 0;
}