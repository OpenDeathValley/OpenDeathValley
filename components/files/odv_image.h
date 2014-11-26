#ifndef OPENDV_IMAGE_H
#define OPENDV_IMAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "odv_file.h"

struct ODVImage
{
    unsigned short width;
    unsigned short height;
    unsigned int type_compression;
    unsigned int data_size;
    unsigned char *buf;
};

struct ODVImage *odv_image_parse(struct ODVFile *file);
void odv_image_info(const struct ODVImage *img);
int odv_image_get_r(short x);
int odv_image_get_g(short x);
int odv_image_get_b(short x);
short odv_image_to_rgb(int r, int g, int b);

void odv_image_clean(struct ODVImage *img);

#endif /* OPENDV_IMAGE_H */
