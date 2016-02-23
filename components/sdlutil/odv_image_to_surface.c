#include "odv_image_to_surface.h"

SDL_Surface* odv_image_to_surface(struct ODVImage *img)
{
    SDL_Surface *surface = NULL;

    surface = SDL_CreateRGBSurface(0, img->width, img->height, 16, 0, 0, 0, 0);
    if (surface == NULL) {
        fprintf(stderr, "[-] odv_image_to_surface - SDL_CreateRGBSurface fail : %s\n", SDL_GetError());
        return NULL;
    }
    SDL_LockSurface(surface);
    memcpy(surface->pixels, img->buf, img->width * img->height * 2);
    SDL_UnlockSurface(surface);
    return surface;
}

