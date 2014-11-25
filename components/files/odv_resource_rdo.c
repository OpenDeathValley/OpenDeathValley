#include "odv_resource_rdo.h"

void *odv_resource_parse_rdo(struct ODVResourceFile *rfile)
{
    struct ODVResourceRdo *rdo = NULL;
    struct ODVImage *entry = NULL;
    unsigned int unk_dword_00;
    unsigned int unk_dword_01;
    int nbentry = 0;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &unk_dword_00, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_rdo - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &unk_dword_01, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_rdo - file read 4 failed\n");
        return NULL;
    }
    rdo = calloc(1, sizeof (struct ODVResourceRdo));
    if (rdo == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_rdo - calloc failed\n");
        return NULL;
    }
    rdo->unk_dword_00 = unk_dword_00;
    rdo->unk_dword_01 = unk_dword_01;
    for (i = 0; i < 7; i++) {
        if ((1 << i) & unk_dword_01)
            nbentry++;
    }
    rdo->nbentry = nbentry;
    rdo->entries = calloc(nbentry, sizeof (struct ODVImage*));
    if (rdo->entries == NULL) {
        free(rdo);
        fprintf(stderr, "[-] odv_resource_parse_rdo - calloc failed\n");
        return NULL;
    }
    for (i = 0; i < rdo->nbentry; i++) {
        entry = odv_image_parse(rfile->file);
        if (entry == NULL) {
            odv_resource_clean_rdo(rdo);
            return NULL;
        }
        rdo->entries[i] = entry;
    }
    return rdo;
}

void odv_resource_rdo_info(const struct ODVResourceRdo *rdo)
{
    int i;

    if (rdo == NULL)
        return;
    printf("[- ODV RESOURCE RDO information -]\n");
    printf("unk_dword_00: 0x%08X\n", rdo->unk_dword_00);
    printf("nbentry: 0x%04X (%d)\n", rdo->nbentry, rdo->nbentry);
    if (rdo->entries) {
        for (i = 0; i < rdo->nbentry; i++) {
            if (rdo->entries[i] != NULL) {
                odv_image_info(rdo->entries[i]);
            }
        }
    }
    printf("[---------------------------------]\n");
}

void odv_resource_clean_rdo(struct ODVResourceRdo *rdo)
{
    int i;

    if (rdo == NULL)
        return;
    if (rdo->entries != NULL) {
        for (i = 0; i < rdo->nbentry; i++) {
            if (rdo->entries[i] != NULL) {
                odv_image_clean(rdo->entries[i]);
                rdo->entries[i] = NULL;
            }
        }
        free(rdo->entries);
    }
    free(rdo);
}