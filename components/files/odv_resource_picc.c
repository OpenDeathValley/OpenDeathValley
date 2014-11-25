#include "odv_resource_picc.h"

void *odv_resource_parse_pic(struct ODVResourceFile *rfile)
{
    struct ODVResourcePicc *picc = NULL;
    struct ODVImage *entry = NULL;
    unsigned int unk_dword_00;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &unk_dword_00, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_pic - file read 4 failed\n");
        return NULL;
    }
    picc = calloc(1, sizeof (struct ODVResourcePicc));
    if (picc == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_pic - calloc failed\n");
        return NULL;
    }
    picc->unk_dword_00 = unk_dword_00;
    picc->nbentry = 1;
    picc->entries = calloc(picc->nbentry, sizeof (struct ODVImage*));
    if (picc->entries == NULL) {
        free(picc);
        fprintf(stderr, "[-] odv_resource_parse_pic - calloc failed\n");
        return NULL;
    }
    for (i = 0; i < picc->nbentry; i++) {
        entry = odv_image_parse(rfile->file);
        if (entry == NULL) {
            odv_resource_clean_picc(picc);
            return NULL;
        }
        picc->entries[i] = entry;
    }
    return picc;
}

void *odv_resource_parse_picc(struct ODVResourceFile *rfile)
{
    struct ODVResourcePicc *picc = NULL;
    struct ODVImage *entry = NULL;
    unsigned int unk_dword_00;
    int nbentry;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &unk_dword_00, 4);
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
    picc->unk_dword_00 = unk_dword_00;
    picc->nbentry = nbentry;
    picc->entries = calloc(nbentry, sizeof (struct ODVImage*));
    if (picc->entries == NULL) {
        free(picc);
        fprintf(stderr, "[-] odv_resource_parse_pic - calloc failed\n");
        return NULL;
    }
    for (i = 0; i < picc->nbentry; i++) {
        entry = odv_image_parse(rfile->file);
        if (entry == NULL) {
            odv_resource_clean_picc(picc);
            return NULL;
        }
        picc->entries[i] = entry;
    }
    return picc;
}

void odv_resource_picc_info(const struct ODVResourcePicc *picc)
{
    int i;

    if (picc == NULL)
        return;
    printf("[- ODV RESOURCE PICC information -]\n");
    printf("unk_dword_00: 0x%08X\n", picc->unk_dword_00);
    printf("nbentry: 0x%04X (%d)\n", picc->nbentry, picc->nbentry);
    if (picc->entries) {
        for (i = 0; i < picc->nbentry; i++) {
            if (picc->entries[i] != NULL) {
                odv_image_info(picc->entries[i]);
            }
        }
    }
    printf("[---------------------------------]\n");
}

void odv_resource_clean_picc(struct ODVResourcePicc *picc)
{
    int i;

    if (picc == NULL)
        return;
    if (picc->entries != NULL) {
        for (i = 0; i < picc->nbentry; i++) {
            if (picc->entries[i] != NULL) {
                odv_image_clean(picc->entries[i]);
                picc->entries[i] = NULL;
            }
        }
        free(picc->entries);
    }
    free(picc);
}