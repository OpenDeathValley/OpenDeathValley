#include "odv_map_handler.h"

struct ODVMap *odv_map_open(const char *filename)
{
    struct ODVFile *file = NULL;
    struct ODVMap *mfile = NULL;

    file = odv_file_open(filename);
    if (file == NULL) {
        fprintf(stderr, "[-] odv_map_open - odv_file_open failed\n");
        return NULL;
    }
    mfile = calloc(1, sizeof (struct ODVMap));
    if (mfile == NULL) {
        fprintf(stderr, "[-] odv_map_open - malloc failed\n");
        odv_file_close(file);
        return NULL;
    }
    mfile->file = file;
    mfile->img = odv_image_parse(mfile->file);
    if (mfile->img == NULL) {
        odv_map_close(mfile);
        return NULL;
    }
    return mfile;
}

void odv_map_info(const struct ODVMap *map)
{
    if (map == NULL)
        return;
    printf("[- ODV MAP information -]\n");
    odv_image_info(map->img);
    printf("[---------------------------------]\n");
}

void odv_map_close(struct ODVMap *mfile)
{
    if (mfile == NULL)
        return;
    if (mfile->file != NULL)
        odv_file_close(mfile->file);
    if (mfile->img != NULL)
        odv_image_clean(mfile->img);
    free(mfile);
}