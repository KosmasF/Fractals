#ifndef LOOP_H
#define LOOP_H

#include <SDL2/SDL.h>
#include "Utils.h"
#include "Save.h"
#include "Update.h"

#define ZOOM_RATIO 1.5f

extern float zoom;
extern cfloat offset;

bool Loop();

#endif
