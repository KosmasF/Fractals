#include "Update.h"

void (*fractal)(cfloat, cfloat*) = mandelbrot_iterative;
cfloat *map;
unsigned int iterations;
bool reset;
bool thread_run;

unsigned int *pixels;

void* update(void*){
    pixels = (unsigned int*)malloc(WIDTH*HEIGHT*sizeof(unsigned int)); 
    map = (cfloat*)malloc(WIDTH*HEIGHT*sizeof(cfloat));
    for(iterations = 0; thread_run; ++iterations){
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                // Convergence res = fractal( (cfloat){
                //         (float)(x - offset.x)/zoom, 
                //         (float)(y - offset.y)/zoom
                //          } );


                Divergence res;
                if(!(map[x + y*WIDTH].x == INFINITY)){
                    fractal( (cfloat){
                            (double)(x - offset.x)/zoom, 
                            (double)(y - offset.y)/zoom
                             } , map + (x + y*WIDTH));
                    if(map[x + y*WIDTH].x == INFINITY){
                        res.diverged = true;
                        res.iterations = iterations;
                        map[x + y*WIDTH].y = iterations;
                    }
                    else{
                        res.diverged = false;
                    } 

                }
                else{
                    res.diverged = true;
                    res.iterations = map[x + y*WIDTH].y;
                }
                    

                uint8_t r, g, b;

                if(!res.diverged){ // [0,2) Black region
                    r = g = b = 0;
                
                }
                else{
                    if (res.iterations < 20){
                        b = (255 * res.iterations/3) / 20 + 0xff/3;
                        r = g = 0;
                    }
                    else{
                        // float x = logf(res.iterations); (15, inf)
                        b = (res.iterations - 20) / (float)(iterations - 20) * (0xff-0xaa) + 0xaa;
                        r = g = (res.iterations - 20) / (float)(iterations - 20) * 0xff;
                        // r = b = g = 255 - (255.f / 89.f * x);
                    }
                }
                // else{ // (2, inf)
                //    float x = logf(res.iterations);
                //    r = b = g = 255 - (255.f / 89.f * x);
                // } 
                
                pixels[y * WIDTH + x] = (255 << 24) | (r << 16) | (g << 8) | b;
            }
        }
        if (reset) {
            reset = false;
            iterations = 0;
        }
    }
    free(map);
    free(pixels);
    return NULL;
}
