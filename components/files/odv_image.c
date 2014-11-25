#include "odv_image.h"

struct ODVImage *odv_image_parse(struct ODVFile *file)
{
    struct ODVImage *img = NULL;
    size_t numberofbytesread = 0;
    unsigned short width;
    unsigned short height;
    unsigned int type_compression;
    unsigned int data_size;
    unsigned char *buf = NULL;

    numberofbytesread = odv_file_read(file, &width, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_image_parse - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(file, &height, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_image_parse - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(file, &type_compression, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_image_parse - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(file, &data_size, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_image_parse - file read 4 failed\n");
        return NULL;
    }
    buf = calloc(data_size, sizeof (char));
    if (buf == NULL) {
        fprintf(stderr, "[-] odv_image_parse - calloc failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(file, buf, data_size);
    if (numberofbytesread != data_size) {
        fprintf(stderr, "[-] odv_image_parse - file read %d failed\n", data_size);
        free(buf);
        return NULL;
    }
    img = calloc(1, sizeof (struct ODVImage));
    if (img == NULL) {
        fprintf(stderr, "[-] odv_image_parse - calloc failed\n");
        free(buf);
        return NULL;
    }
    img->width = width;
    img->height = height;
    img->type_compression = type_compression;
    /*
        TODO: ADD CODE TO UNCOMPRESS
        - 0: RAW ?
        - 1: ZLIB
        - 2: BZ2
    */
    img->data_size = data_size;
    img->buf = buf;
    return img;
}

void odv_image_info(const struct ODVImage *img)
{
    if (img == NULL)
        return;
    printf("[- ODV IMAGE information -]\n");
    printf("width : 0x%04X\n", img->width);
    printf("height: 0x%04X\n", img->height);
    printf("type_compression: 0x%08X\n", img->type_compression);
    printf("data_size: 0x%08X\n", img->data_size);
    printf("[---------------------------------]\n");
}

void odv_image_clean(struct ODVImage *img)
{
    if (img == NULL)
        return;
    if (img->buf != NULL)
        free(img->buf);
    free(img);
}