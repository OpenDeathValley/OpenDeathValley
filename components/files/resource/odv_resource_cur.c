#include "odv_resource_cur.h"

void *odv_resource_parse_cur(struct ODVResourceFile *rfile)
{
    struct ODVResourceCur *cur = NULL;
    unsigned int useless;
    unsigned short tick_count_redraw;
    unsigned short hit_point_y;
    unsigned short hit_point_x;
    unsigned short tick_count_redraw_per_image;
    int nbentry = 0;
    size_t numberofbytesread = 0;

    numberofbytesread = odv_file_read(rfile->file, &useless, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_cur - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &tick_count_redraw, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_resource_parse_cur - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &hit_point_y, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_resource_parse_cur - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &hit_point_x, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_resource_parse_cur - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &tick_count_redraw_per_image, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_resource_parse_cur - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &nbentry, 4);
    if (numberofbytesread != 4 || nbentry < 0) {
        fprintf(stderr, "[-] odv_resource_parse_cur - file read 4 failed\n");
        return NULL;
    }
    cur = calloc(1, sizeof (struct ODVResourceCur));
    if (cur == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_cur - calloc failed\n");
        return NULL;
    }
    cur->useless = useless;
    cur->tick_count_redraw = tick_count_redraw;
    cur->hit_point_y = hit_point_y;
    cur->hit_point_x = hit_point_x;
    cur->tick_count_redraw_per_image = tick_count_redraw_per_image;
    cur->nbentry = nbentry;
    cur->imgmap = odv_imagemap_parse_nb(rfile->file, cur->nbentry);
    if (cur->imgmap == NULL) {
        free(cur);
        return NULL;
    }
    return cur;
}

void odv_resource_cur_info(const struct ODVResourceCur *cur)
{
    if (cur == NULL)
        return;
    printf("[- ODV RESOURCE CUR information -]\n");
    printf("useless                     : 0x%08X\n", cur->useless);
    printf("tick_count_redraw           : 0x%04X\n", cur->tick_count_redraw);
    printf("hit_point_y                 : 0x%04X\n", cur->hit_point_y);
    printf("hit_point_x                 : 0x%04X\n", cur->hit_point_x);
    printf("tick_count_redraw_per_image : 0x%04X\n", cur->tick_count_redraw_per_image);
    printf("nbentry: 0x%04X (%d)\n", cur->nbentry, cur->nbentry);
    if (cur->imgmap != NULL) {
        odv_imagemap_info(cur->imgmap);
    }
    printf("[---------------------------------]\n");
}

void odv_resource_cur_extract(const struct ODVResourceCur *picc, const char *filename, const char *output, unsigned int id)
{
    char suffix[256];

    snprintf(suffix, sizeof (suffix) - 1, "%d", id);

    odv_imagemap_extract(picc->imgmap, filename, output, suffix);
}

void odv_resource_clean_cur(struct ODVResourceCur *cur)
{
    if (cur == NULL)
        return;
    if (cur->imgmap != NULL)
        odv_imagemap_clean(cur->imgmap);
    free(cur);
}