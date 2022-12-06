#ifndef OPENDV_TEST_H
#define OPENDV_TEST_H

#include <SDL.h>

#include "odv_resource_handler.h"
#include "odv_scb_handler.h"
#include "odv_fxg_handler.h"
#include "odv_dvd_handler.h"
#include "odv_map_handler.h"
#include "odv_dvm_handler.h"
#include "odv_sxt_handler.h"
#include "odv_fnt_handler.h"
#include "odv_dvf_handler.h"

#include "odv_image_to_surface.h"

void odv_rend_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

#endif /* OPENDV_TEST_H */