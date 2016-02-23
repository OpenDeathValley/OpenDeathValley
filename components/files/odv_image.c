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
    unsigned char *buf_ucomp = 0x00;
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
    //else if (img->type_compression == 0x02) {
    //    /* BZ2 */
    //    length_dst = img->width * img->height * 3;
    //    buf_ucomp = calloc(length_dst, sizeof (char));
    //    if (buf_ucomp == NULL) {
    //        fprintf(stderr, "[-] odv_image_parse - calloc failed\n");
    //        free(img);
    //        free(buf);
    //        return NULL;
    //    }
    //    
    //    
    //    
    //    fprintf(stderr, "[-] odv_image_parse - BZ2 not supported yet\n");
    //    free(img);
    //    free(buf);
    //    return NULL;
    //}
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
    printf("width : 0x%04X\n", img->width);
    printf("height: 0x%04X\n", img->height);
    printf("type_compression: 0x%08X\n", img->type_compression);
    printf("data_size: 0x%08X\n", img->data_size);
    printf("[-------------------------]\n");
}

int odv_image_get_r(short x)
{
    return ((x >> 8) & 0xF8);
}

int odv_image_get_g(short x)
{
    return ((x >> 3) & 0xFC);
}

int odv_image_get_b(short x)
{
    return ((x << 3) & 0xFF);
}

short odv_image_to_rgb(int r, int g, int b)
{
    return (short)(((r << 8) & 0xf800) | ((g << 3) & 0x07e0) | (b >> 3));
}

void odv_image_clean(struct ODVImage *img)
{
    if (img == NULL)
        return;
    if (img->buf != NULL)
        free(img->buf);
    free(img);
}