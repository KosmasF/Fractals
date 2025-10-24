#include <SDL2/SDL.h>
#include <Loop.h>
#include <stdio.h>
#include <pthread.h>
#include "Mandelbrot.h"
#include "Julia.h"

#define WIDTH (1920)
#define HEIGHT (1080)

uint32_t pixels[WIDTH * HEIGHT];
float zoom = 1.f/4.2f*WIDTH;
cfloat offset = {WIDTH/2.f, HEIGHT/2.f};

pthread_t thread;
bool thread_run;

void* update(void*);

Convergence (*fractal)(cfloat) = julia;

int main(){
   
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Falling Sand", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);
    // SDL_ShowCursor(false);

    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH, HEIGHT
    );

    thread_run = true;
    pthread_create(&thread, NULL, update, NULL);

    
    while(Loop()){ 
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(renderer);
       
        
        SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(uint32_t));
        
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(win);
    }

    
    printf("Terminating ...\n");
    thread_run = false;
    pthread_join(thread, NULL);        
    
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

void* update(void*){ 
    while(thread_run){
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                Convergence res = fractal( (cfloat){
                        (float)(x - offset.x)/zoom, 
                        (float)(y - offset.y)/zoom
                         } );

                uint8_t r, g, b;

                if(res.converged){ // [0,2) Black region
                    r = g = b = 0;
                
                }
                else{
                    if (res.iterations < 20){
                        b = (255 * res.iterations/3) / 20 + 0xff/3;
                        r = g = 0;
                    }
                    else{
                        // float x = logf(res.iterations); (15, inf)
                        b = (res.iterations - 20) / (float)(NUM_ITERATIONS - 20) * (0xff-0xaa) + 0xaa;
                        r = g = (res.iterations - 20) / (float)(NUM_ITERATIONS - 20) * 0xff;
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
    }
    return NULL;
}
