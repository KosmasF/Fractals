#ifndef UPDATE_H
#define UPDATE_H

#include "Mandelbrot.h"
#include "Julia.h"
#include <stdlib.h>

void* update(void*);
extern void (*fractal)(cfloat, cfloat*);
extern cfloat* map;
extern bool reset;
extern bool thread_run;
extern unsigned int *pixels;

extern float zoom;
extern cfloat offset;

#endif
