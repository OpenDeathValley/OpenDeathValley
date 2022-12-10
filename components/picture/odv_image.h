#ifndef OPENDV_IMAGE_H
#define OPENDV_IMAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "odv_file.h"
#include "odv_utils.h"

#include <zlib.h>
#include <bzlib.h>

struct ODVImage
{
    unsigned short width;
    unsigned short height;
    unsigned int type_compression;
    unsigned int data_size;
    unsigned char *buf;
};

#define BMP_HEADER_SIZE             0x0E
#define BMP_INFO_HEADER_SIZE        0x28
#define BMP_NO_COMPRESION           0x00
#define BMP_MAX_NUMBER_OF_COLORS    0x00
#define BMP_ALL_COLORS_REQUIRED     0x00

#pragma pack(push, 1)
struct BMPHeader
{
    unsigned short type;
    unsigned int size;
    unsigned int reserved;
    unsigned int offset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BMPInfoHeader
{
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short num_planes;
    unsigned short bits_per_pixel;
    unsigned int compression;
    unsigned int image_size_bytes;
    unsigned int x_resolution_ppm;
    unsigned int y_resolution_ppm;
    unsigned int num_colors;
    unsigned int important_colors;
};
#pragma pack(pop)

struct ODVImage *odv_image_parse(struct ODVFile *file);
void odv_image_info(const struct ODVImage *img);
unsigned char odv_image_get_r(unsigned short x);
unsigned char odv_image_get_g(unsigned short x);
unsigned char odv_image_get_b(unsigned short x);
short odv_image_to_rgb(int r, int g, int b);
void odv_image_clean(struct ODVImage *img);
int odv_image_to_bmp(struct ODVImage *img, const char *bmp_filename);
int odv_image_to_bmp_ex(struct ODVImage *img, const char *bmp_filename, unsigned int width, unsigned int height, unsigned int x, unsigned int y);

#endif /* OPENDV_IMAGE_H */
