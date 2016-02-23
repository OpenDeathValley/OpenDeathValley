#ifndef OPENDV_IMAGE_MAP_H
#define OPENDV_IMAGE_MAP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "odv_image.h"

struct ODVImageMap
{
    unsigned int image_count;
    struct ODVImage **images;
};

struct ODVImageMap *odv_imagemap_new(struct ODVFile *file);
int odv_imagemap_radd(struct ODVImageMap *imgmap, struct ODVFile *file);
int odv_imagemap_add(struct ODVImageMap *imgmap, struct ODVImage *img);
void odv_imagemap_info(const struct ODVImageMap *imgmap);
void odv_imagemap_clean(struct ODVImageMap *imgmap);

#endif /* OPENDV_IMAGE_MAP_H */
