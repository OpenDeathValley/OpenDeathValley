#include "odv_resource_picc.h"

void *odv_resource_parse_pic(struct ODVResourceFile *rfile)
{
    struct ODVResourcePicc *picc = NULL;
    unsigned int useless;
    size_t numberofbytesread = 0;

    numberofbytesread = odv_file_read(rfile->file, &useless, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_pic - file read 4 failed\n");
        return NULL;
    }
    picc = calloc(1, sizeof (struct ODVResourcePicc));
    if (picc == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_pic - calloc failed\n");
        return NULL;
    }
    picc->useless = useless;
    picc->nbentry = 1;
    picc->imgmap = odv_imagemap_parse_nb(rfile->file, picc->nbentry);
    if (picc->imgmap == NULL) {
        free(picc);
        return NULL;
    }
    return picc;
}

void *odv_resource_parse_picc(struct ODVResourceFile *rfile)
{
    struct ODVResourcePicc *picc = NULL;
    unsigned int useless;
    int nbentry;
    size_t numberofbytesread = 0;

    numberofbytesread = odv_file_read(rfile->file, &useless, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_picc - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &nbentry, 4);
    if (numberofbytesread != 4 || nbentry < 0) {
        fprintf(stderr, "[-] odv_resource_parse_picc - file read 4 failed\n");
        return NULL;
    }
    picc = calloc(1, sizeof (struct ODVResourcePicc));
    if (picc == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_picc - calloc failed\n");
        return NULL;
    }
    picc->useless = useless;
    picc->nbentry = nbentry;
    picc->imgmap = odv_imagemap_parse_nb(rfile->file, picc->nbentry);
    if (picc->imgmap == NULL) {
        free(picc);
        return NULL;
    }
    return picc;
}

void odv_resource_picc_info(const struct ODVResourcePicc *picc)
{
    if (picc == NULL)
        return;
    printf("[- ODV RESOURCE PICC information -]\n");
    printf("useless: 0x%08X\n", picc->useless);
    printf("nbentry: 0x%04X (%d)\n", picc->nbentry, picc->nbentry);
    if (picc->imgmap != NULL) {
        odv_imagemap_info(picc->imgmap);
    }
    printf("[---------------------------------]\n");
}

void odv_resource_clean_picc(struct ODVResourcePicc *picc)
{
    if (picc == NULL)
        return;
    if (picc->imgmap != NULL)
        odv_imagemap_clean(picc->imgmap);
    free(picc);
}