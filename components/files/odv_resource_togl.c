#include "odv_resource_togl.h"

void *odv_resource_parse_togl(struct ODVResourceFile *rfile)
{
    struct ODVResourceTogl *togl = NULL;
    unsigned int useless;
    unsigned int nb_entry_bit;
    int nbentry = 0;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &useless, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_togl - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &nb_entry_bit, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_togl - file read 4 failed\n");
        return NULL;
    }
    togl = calloc(1, sizeof (struct ODVResourceTogl));
    if (togl == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_togl - calloc failed\n");
        return NULL;
    }
    togl->useless = useless;
    togl->nb_entry_bit = nb_entry_bit;
    for (i = 0; i < 5; i++) {
        if ((1 << i) & nb_entry_bit)
            nbentry++;
    }
    togl->nbentry = nbentry;
    togl->imgmap = odv_imagemap_parse_nb(rfile->file, togl->nbentry);
    if (togl->imgmap == NULL) {
        free(togl);
        return NULL;
    }
    return togl;
}

void odv_resource_togl_info(const struct ODVResourceTogl *togl)
{
    if (togl == NULL)
        return;
    printf("[- ODV RESOURCE TOGL information -]\n");
    printf("useless: 0x%08X\n", togl->useless);
    printf("nb_entry_bit: 0x%08X\n", togl->nb_entry_bit);
    printf("nbentry: 0x%04X (%d)\n", togl->nbentry, togl->nbentry);
    if (togl->imgmap != NULL) {
        odv_imagemap_info(togl->imgmap);
    }
    printf("[---------------------------------]\n");
}

void odv_resource_clean_togl(struct ODVResourceTogl *togl)
{
    if (togl == NULL)
        return;
    if (togl->imgmap != NULL)
        odv_imagemap_clean(togl->imgmap);
    free(togl);
}