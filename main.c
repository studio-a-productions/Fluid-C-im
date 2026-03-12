// app incl
//#include "app.h"

// cim incl
#include "cim.h"
#include "cim_error.h" // to handle errors
#include "cim_particle.h"

// initial window size
// we're doing a 8:6/4:3 ratio to match the CANVAS
#define W_W 800
#define W_H 600
// canvas size (upscale 4)
#define CANVAS_W 200
#define CANVAS_H 150

#define PARTICLE_BUFFER_S 100

int main(int argc, char *argv[]) {
    if (Cim_Init()) {
        printf("EH?");
        Cim_Quit();
        return 1;
    }
    
    struct Cim_ParticleBuffer* pbuffer = Cim_InitPBuffer(PARTICLE_BUFFER_S);
    if (!pbuffer) {
        printf("HELP!!!!");
        Cim_Quit();
        return 1;
    }

    const float4 mvar = {0.0F, 2.1F, 0.52F, 0.0F};
    Cim_CreateParticle(pbuffer, mvar, 0U);
    Cim_UpdatePBufferPos(pbuffer);

    Cim_Log(CIM_LOGTYPE_INFO, "I work");

    if (Cim_Quit()) return 1;
    else return 0;
}