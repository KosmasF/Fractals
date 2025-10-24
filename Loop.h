#ifndef LOOP_H
#define LOOP_H

#include <SDL2/SDL.h>
#include "Utils.h"

#define ZOOM_RATIO 1.5f

extern float zoom;
extern cfloat offset;
extern Convergence (*fractal)(cfloat);

bool Loop();

#endif
