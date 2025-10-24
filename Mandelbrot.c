#include "Mandelbrot.h"

cfloat INITIAL_Z = {0,0};

Convergence mandelbrot(cfloat input){    
    cfloat z0 = INITIAL_Z;
    for(int i = 0; i <= NUM_ITERATIONS;++i){
        cfloat z1 = addc(mulc(z0, z0), input);

        if(absc(z1) > 2.f) return (Convergence){ false, i };
        z0 = z1;
    }

    return (Convergence){ true, 0 };
}
