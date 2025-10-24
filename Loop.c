#include "Loop.h"
#include "Mandelbrot.h"
#include "Julia.h"

bool mouse_pressed = false;
extern cfloat INITIAL_Z;
extern cfloat INITIAL_C;

bool Loop()
{
	SDL_Event e;

	while( SDL_PollEvent( &e ) != 0 ) {
        if(e.type == SDL_QUIT)
        {
            return false;
        }
        if(e.type == SDL_MOUSEWHEEL){
            SDL_Keymod mod = SDL_GetModState();
            if(mod & KMOD_SHIFT){
                INITIAL_Z.x += 0.05f*e.wheel.y;
                INITIAL_C.x += 0.05f*e.wheel.y;
            }
            if(mod & KMOD_CTRL){
                INITIAL_Z.y += 0.05f*e.wheel.y;
                INITIAL_C.y += 0.05f*e.wheel.y;
            }
            if(!mod){
                float scale =  e.wheel.y < 0 ?  1.f/ZOOM_RATIO : ZOOM_RATIO;
                zoom *= scale;
                offset.x = - (((e.wheel.mouseX - offset.x) * zoom) / (zoom / scale) - e.wheel.mouseX);
                offset.y = - (((e.wheel.mouseY- offset.y) * zoom) / (zoom / scale) - e.wheel.mouseY);
            }
        }
        else if(e.type == SDL_MOUSEMOTION)
        {
            if(mouse_pressed){
                offset.x += e.motion.xrel;
                offset.y += e.motion.yrel;
            }
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            mouse_pressed = true;
        }
        else if(e.type == SDL_MOUSEBUTTONUP)
        {
            mouse_pressed = false;
        } 
        else if(e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_j:
                    fractal = julia;
                    break;
                case SDLK_m:
                    fractal = mandelbrot;
                    break;
            }
        }
    }
    return true;
}
