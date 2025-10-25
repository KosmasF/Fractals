#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1080

typedef struct{
    double x;
    double y;
} cfloat;

typedef struct{
    bool diverged;
    uint32_t iterations;
} Divergence;

cfloat addc(cfloat a, cfloat b);

cfloat mulc(cfloat a, cfloat b);

float absc(cfloat a);

#endif
