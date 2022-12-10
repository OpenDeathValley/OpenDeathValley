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
    unsigned char *buf_ucomp = NULL;
    uLongf length_dst = 0x00;
    int uncomp_return = 0;

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
    if (img->type_compression == 0x00) {
        /* RAW */
        img->data_size = data_size;
        img->buf = buf;
    }
    else if (img->type_compression == 0x01 || img->type_compression == 0x02) {
        /* ZLIB OR BZ2 */
        length_dst = img->width * img->height * 2;  /* R5G6B */
        buf_ucomp = calloc(length_dst, sizeof (char));
        if (buf_ucomp == NULL) {
            fprintf(stderr, "[-] odv_image_parse - calloc failed\n");
            free(img);
            free(buf);
            return NULL;
        }
        if (img->type_compression == 0x01) {
            /* ZLIB */
            uncomp_return = uncompress(buf_ucomp, &length_dst, buf, data_size);
            if (uncomp_return != Z_OK) {
                fprintf(stderr, "[-] odv_image_parse - uncompress failed : %d\n", uncomp_return);
                free(buf_ucomp);
                free(img);
                free(buf);
                return NULL;
            }
        }
        else if (img->type_compression == 0x02) {
            /* BZ2 */
            uncomp_return = BZ2_bzBuffToBuffDecompress((char*)buf_ucomp, (unsigned int*)&length_dst, (char*)buf, data_size, 0x00, 0x00);
            if (uncomp_return != BZ_OK) {
                fprintf(stderr, "[-] odv_image_parse - BZ2_bzBuffToBuffDecompress failed : %d\n", uncomp_return);
                free(buf_ucomp);
                free(img);
                free(buf);
                return NULL;
            }
        }
        img->buf = buf_ucomp;
        img->data_size = length_dst;
        free(buf);
    }
    else {
        fprintf(stderr, "[-] odv_image_parse - %d type compression not supported\n", img->type_compression);
        free(img);
        free(buf);
        return NULL;
    }
    return img;
}

void odv_image_info(const struct ODVImage *img)
{
    if (img == NULL)
        return;
    printf("[- ODV IMAGE information -]\n");
    printf("width : 0x%04X (%d)\n", img->width, img->width);
    printf("height: 0x%04X (%d)\n", img->height, img->height);
    printf("type_compression: 0x%08X\n", img->type_compression);
    printf("data_size: 0x%08X\n", img->data_size);
    printf("[-------------------------]\n");
}

unsigned char odv_image_get_r(unsigned short x)
{
    return ((x >> 8) & 0xF8);
}

unsigned char odv_image_get_g(unsigned short x)
{
    return ((x >> 3) & 0xFC);
}

unsigned char odv_image_get_b(unsigned short x)
{
    return ((x << 3) & 0xFF);
}

short odv_image_to_rgb(int r, int g, int b)
{
    return (short)(((r << 8) & 0xf800) | ((g << 3) & 0x07e0) | (b >> 3));
}

void odv_image_clean(struct ODVImage *img)
{
    if (img == NULL) {
        return;
    }
    if (img->buf != NULL) {
        free(img->buf);
        img->buf = NULL;
    }
    free(img);
}

int odv_image_to_bmp(struct ODVImage *img, const char *bmp_filename)
{
    struct BMPHeader bmp_header;
    struct BMPInfoHeader bmp_info_header;
    unsigned int alignedwidth = 0;
    FILE *outputFile = NULL;
    unsigned char color[3];

    outputFile = fopen(bmp_filename, "wb");
    if (outputFile == NULL) {
        fprintf(stderr, "fopen failed for %s\n", bmp_filename);
        return 1;
    }
    alignedwidth = align4(img->width);
    bmp_header.type = 0x4d42; // "BM"
    bmp_header.size = (alignedwidth * img->height) + BMP_HEADER_SIZE + BMP_INFO_HEADER_SIZE;
    bmp_header.reserved = 0x00;
    bmp_header.offset = BMP_HEADER_SIZE + BMP_INFO_HEADER_SIZE;
    fwrite(&bmp_header, sizeof (struct BMPHeader), 1, outputFile);
    bmp_info_header.header_size = BMP_INFO_HEADER_SIZE;
    bmp_info_header.width = alignedwidth;
    bmp_info_header.height = img->height;
    bmp_info_header.num_planes = 0x01;
    bmp_info_header.bits_per_pixel = 24;
    bmp_info_header.compression = BMP_NO_COMPRESION;
    bmp_info_header.image_size_bytes = img->width * img->height * (bmp_info_header.bits_per_pixel / 8);
    bmp_info_header.x_resolution_ppm = 0;
    bmp_info_header.y_resolution_ppm = 0;
    bmp_info_header.num_colors = BMP_MAX_NUMBER_OF_COLORS;
    bmp_info_header.important_colors = BMP_ALL_COLORS_REQUIRED;
    fwrite(&bmp_info_header, sizeof (struct BMPInfoHeader), 1, outputFile);
    for (unsigned int i = 0; i < img->height; i++) {
        for (unsigned int j = 0; j < img->width; j++) {
            unsigned short pixel = *(unsigned short*)((unsigned char*)img->buf + ((((img->height - 1 - i) * img->width) + j) * 2));
            color[2] = odv_image_get_r(pixel);
            color[1] = odv_image_get_g(pixel);
            color[0] = odv_image_get_b(pixel);
            fwrite(&color, sizeof (unsigned char), 3, outputFile);
        }
        for (unsigned int j = 0; j < (alignedwidth - img->width); j++) {
            color[0] = 0;
            color[1] = 0xFF;
            color[2] = 0;
            fwrite(&color, sizeof (unsigned char), 3, outputFile);
        }
    }

    fclose(outputFile);

    return 0;
}

int odv_image_to_bmp_ex(struct ODVImage *img, const char *bmp_filename, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
{
    struct BMPHeader bmp_header;
    struct BMPInfoHeader bmp_info_header;
    unsigned int alignedwidth = 0;
    FILE *outputFile = NULL;
    unsigned char color[3];

    outputFile = fopen(bmp_filename, "wb");
    if (outputFile == NULL) {
        fprintf(stderr, "fopen failed for %s\n", bmp_filename);
        return 1;
    }
    // TODO it's already aligned :/
    alignedwidth = align4(width);
    width = alignedwidth;
    bmp_header.type = 0x4d42; // "BM"
    bmp_header.size = (alignedwidth * height) + BMP_HEADER_SIZE + BMP_INFO_HEADER_SIZE;
    bmp_header.reserved = 0x00;
    bmp_header.offset = BMP_HEADER_SIZE + BMP_INFO_HEADER_SIZE;
    fwrite(&bmp_header, sizeof (struct BMPHeader), 1, outputFile);
    bmp_info_header.header_size = BMP_INFO_HEADER_SIZE;
    bmp_info_header.width = width;
    bmp_info_header.height = height;
    bmp_info_header.num_planes = 0x01;
    bmp_info_header.bits_per_pixel = 24;
    bmp_info_header.compression = BMP_NO_COMPRESION;
    bmp_info_header.image_size_bytes = width * height * (bmp_info_header.bits_per_pixel / 8);
    bmp_info_header.x_resolution_ppm = 0;
    bmp_info_header.y_resolution_ppm = 0;
    bmp_info_header.num_colors = BMP_MAX_NUMBER_OF_COLORS;
    bmp_info_header.important_colors = BMP_ALL_COLORS_REQUIRED;
    fwrite(&bmp_info_header, sizeof (struct BMPInfoHeader), 1, outputFile);

    unsigned char *data = malloc(height * width * 0x02);
    memset(data, 0x00, height * width * 0x02);
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            *(unsigned short*)((unsigned char*)data + ((((i * width)) + j) * 2)) = 0x7C0;
        }
    }
    for (unsigned int i = y; i < height; i++) {
        for (unsigned int j = 0; j < x; j++) {
            *(unsigned short*)((unsigned char*)data + ((((i * width)) + j) * 2)) = 0x7C0;
        }
    }

    for (unsigned int i = 0; i < img->height; i++) {
        for (unsigned int j = 0; j < img->width; j++) {
            unsigned pos = (y * width + x) * 2;
            pos = pos + ((((i * width)) + j) * 2);
            // dbg
            //if (i == 0 || j == 0 || i == (unsigned int)(img->height - 1) || j == (unsigned int)(img->width - 1)) {
            //    *(unsigned short*)((unsigned char*)data + pos) = 0xF8 << 8;
            //}
            //else {
                *(unsigned short*)((unsigned char*)data + pos) = *(unsigned short*)((unsigned char*)img->buf + ((i * img->width) + j) * 2);
            //}
        }
    }

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
             unsigned short pixel = *(unsigned short*)((unsigned char*)data + ((((height - 1 - i) * width) + j) * 2));
            color[2] = odv_image_get_r(pixel);
            color[1] = odv_image_get_g(pixel);
            color[0] = odv_image_get_b(pixel);
            fwrite(&color, sizeof (unsigned char), 3, outputFile);
        }
    }
    free(data);
    fclose(outputFile);
    return 0;
}