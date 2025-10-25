#include "Save.h"

void Save(void) {
    SDL_Surface *sshot = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    char buffer[256];
    sprintf(buffer, "Screenshot: %li.bmp", time(NULL)); 
    printf("Saved screenshot in ./%s\n", buffer);
    SDL_SaveBMP(sshot, buffer);
    SDL_FreeSurface(sshot);
}
