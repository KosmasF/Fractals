#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "Utils.h" 

#define NUM_ITERATIONS 100

Divergence mandelbrot(cfloat input); 
void mandelbrot_iterative(cfloat input, cfloat* map_coord);

#endif
