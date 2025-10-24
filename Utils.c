#include "Utils.h"

cfloat addc(cfloat a, cfloat b){
    return (cfloat){a.x + b.x, a.y + b.y};
}

cfloat mulc(cfloat a, cfloat b){
    return (cfloat){a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};
}

float absc(cfloat a){
    return sqrtf(a.x*a.x + a.y*a.y);
}
