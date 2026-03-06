#include "cim_particle.h"
#ifdef CIM_PARTICLE_H
#ifndef CIM_PBEHAVIOR_H
#define CIM_PBEHAVIOR_H

/*
    Cim Behavior may be refered to as Cim Behaviour, though not
        in code, as no such duplicate exists.
    Cim Particle Behaviour is directly responsible for updating
        the particle's data, though this will be done via the
        Cim Particle Buffer. 
    Anyhow, Cim Particle Behaviour works on a type-basis, where 
        the type buffer shall work as an index of a long table.
        This ensures data shan't be copied for particles of the
        same type. Unfortunately, adding more type shall result
        in the addition of more functions. 
    Cim Particle Behaviour provides functions to help optimise 
        the recursive updates, because by this definition every 
        particle that updates anything but itself will result in
        repeated calls to every particle in the buffer. That is
        thus the reason you can create pointer arrays to the 
        members that are of the same type, and thus you can pass
        those.
    Cim Particle Behaviour is not public to Cim, it is a private
        header that solely belongs to Cim Particle, even though 
        it itself is a member of Cim.
*/

#endif
#endif