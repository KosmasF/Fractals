#include <SDL2/SDL.h>
#include <Loop.h>
#include <stdio.h>
#include <pthread.h>
#include "Mandelbrot.h"
#include "Julia.h"
#include "Update.h"

float zoom = 1.f/4.2f*WIDTH;
cfloat offset = {WIDTH/2.f, HEIGHT/2.f};

pthread_t thread;

SDL_Window* win;
SDL_Renderer* renderer;

int main(){
   
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Fractal Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, 0);
    // SDL_ShowCursor(false);
    // SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);

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
