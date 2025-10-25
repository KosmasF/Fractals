#include "Mandelbrot.h"

cfloat INITIAL_Z = {0,0};

Divergence mandelbrot(cfloat input){    
    cfloat z0 = INITIAL_Z;
    for(int i = 0; i <= NUM_ITERATIONS;++i){
        cfloat z1 = addc(mulc(z0, z0), input);

        if(absc(z1) > 2.f) return (Divergence){ true, i };
        z0 = z1;
    }

    return (Divergence){ false, 0 };
}

void mandelbrot_iterative(cfloat input, cfloat* map_coord){    
    cfloat z0 = *map_coord;
    cfloat z1 = addc(mulc(z0, z0), input);
   
    if(absc(z1) > 2.f){
        (*map_coord).x = INFINITY;
        return;
    }
    *map_coord = z1;
    
    return;
}
