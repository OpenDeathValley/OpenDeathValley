#include "odv_resource_togl.h"

void *odv_resource_parse_togl(struct ODVResourceFile *rfile)
{
    struct ODVResourceTogl *togl = NULL;
    struct ODVImage *entry = NULL;
    unsigned int unk_dword_00;
    unsigned int unk_dword_01;
    int nbentry = 0;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &unk_dword_00, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_togl - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &unk_dword_01, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_togl - file read 4 failed\n");
        return NULL;
    }
    togl = calloc(1, sizeof (struct ODVResourceTogl));
    if (togl == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_togl - calloc failed\n");
        return NULL;
    }
    togl->unk_dword_00 = unk_dword_00;
    togl->unk_dword_01 = unk_dword_01;
    for (i = 0; i < 5; i++) {
        if ((1 << i) & unk_dword_01)
            nbentry++;
    }
    togl->nbentry = nbentry;
    togl->entries = calloc(nbentry, sizeof (struct ODVImage*));
    for (i = 0; i < togl->nbentry; i++) {
        entry = odv_image_parse(rfile->file);
        if (entry == NULL) {
            odv_resource_clean_togl(togl);
            return NULL;
        }
        togl->entries[i] = entry;
    }
    return togl;
}

void odv_resource_togl_info(const struct ODVResourceTogl *togl)
{
    int i;

    if (togl == NULL)
        return;
    printf("[- ODV RESOURCE TOGL information -]\n");
    printf("unk_dword_00: 0x%08X\n", togl->unk_dword_00);
    printf("nbentry: 0x%04X (%d)\n", togl->nbentry, togl->nbentry);
    if (togl->entries) {
        for (i = 0; i < togl->nbentry; i++) {
            if (togl->entries[i] != NULL) {
                odv_image_info(togl->entries[i]);
            }
        }
    }
    printf("[---------------------------------]\n");
}

void odv_resource_clean_togl(struct ODVResourceTogl *togl)
{
    int i;

    if (togl == NULL)
        return;
    if (togl->entries != NULL) {
        for (i = 0; i < togl->nbentry; i++) {
            if (togl->entries[i] != NULL) {
                odv_image_clean(togl->entries[i]);
                togl->entries[i] = NULL;
            }
        }
        free(togl->entries);
    }
    free(togl);
}