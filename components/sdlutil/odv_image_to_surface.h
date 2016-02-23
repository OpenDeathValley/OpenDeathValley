#ifndef OPENDV_IMAGE_TO_SURFACE_H
#define OPENDV_IMAGE_TO_SURFACE_H

#include <SDL_surface.h>

#include "odv_image.h"

SDL_Surface* odv_image_to_surface(struct ODVImage *img);

#endif /* OPENDV_IMAGE_TO_SURFACE_H */

