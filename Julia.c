#include "Julia.h"

cfloat INITIAL_C = {0.f,0.f};

Divergence julia(cfloat input){
    cfloat z0 = input;
    for(int i = 0; i <= NUM_ITERATIONS;++i){
        cfloat z1 = addc(mulc(z0, z0), INITIAL_C);

        if(absc(z1) > 2.f) return (Divergence){ true, i };
        z0 = z1;
    }

    return (Divergence){ false, 0 };
}
