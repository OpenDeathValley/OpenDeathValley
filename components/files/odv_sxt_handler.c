#include "odv_sxt_handler.h"

struct ODVSxt *odv_sxt_open(const char *filename)
{
    struct ODVFile *file = NULL;
    struct ODVSxt *sxt = NULL;

    file = odv_file_open(filename);
    if (file == NULL) {
        fprintf(stderr, "[-] odv_sxt_open - odv_file_open failed\n");
        return NULL;
    }
    sxt = calloc(1, sizeof (struct ODVSxt));
    if (sxt == NULL) {
        fprintf(stderr, "[-] odv_sxt_open - malloc failed\n");
        odv_file_close(file);
        return NULL;
    }
    sxt->file = file;
    sxt->img = odv_image_parse(sxt->file);
    if (sxt->img == NULL) {
        odv_sxt_close(sxt);
        return NULL;
    }
    return sxt;
}

void odv_sxt_info(const struct ODVSxt *sxt)
{
    if (sxt == NULL)
        return;
    printf("[- ODV SXT information -]\n");
    odv_image_info(sxt->img);
    printf("[---------------------------------]\n");
}

void odv_sxt_close(struct ODVSxt *sxt)
{
    if (sxt == NULL)
        return;
    if (sxt->file != NULL)
        odv_file_close(sxt->file);
    if (sxt->img != NULL)
        odv_image_clean(sxt->img);
    free(sxt);
}