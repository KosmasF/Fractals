#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <math.h>

typedef struct{
    float x;
    float y;
} cfloat;

typedef struct{
    bool converged;
    uint32_t iterations;
} Convergence;

cfloat addc(cfloat a, cfloat b);

cfloat mulc(cfloat a, cfloat b);

float absc(cfloat a);

#endif
