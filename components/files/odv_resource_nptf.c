#include "odv_resource_nptf.h"

void *odv_resource_parse_nptf(struct ODVResourceFile *rfile)
{
    struct ODVResourceNptf *nptf = NULL;
    struct ODVImage *entry = NULL;
    unsigned int unk_dword_00;
    unsigned int unk_dword_01;
    int nbentry = 0;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &unk_dword_00, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_nptf - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &unk_dword_01, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_nptf - file read 4 failed\n");
        return NULL;
    }
    nptf = calloc(1, sizeof (struct ODVResourceNptf));
    if (nptf == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_nptf - calloc failed\n");
        return NULL;
    }
    nptf->unk_dword_00 = unk_dword_00;
    nptf->unk_dword_01 = unk_dword_01;
    for (i = 0; i < 6; i++) {
        if ((1 << i) & unk_dword_01)
            nbentry++;
    }
    nptf->nbentry = nbentry;
    nptf->entries = calloc(nbentry, sizeof (struct ODVImage*));
    if (nptf->entries == NULL) {
        free(nptf);
        fprintf(stderr, "[-] odv_resource_parse_nptf - calloc failed\n");
        return NULL;
    }
    for (i = 0; i < nptf->nbentry; i++) {
        entry = odv_image_parse(rfile->file);
        if (entry == NULL) {
            odv_resource_clean_nptf(nptf);
            return NULL;
        }
        nptf->entries[i] = entry;
    }
    return nptf;
}

void odv_resource_nptf_info(const struct ODVResourceNptf *nptf)
{
    int i;

    if (nptf == NULL)
        return;
    printf("[- ODV RESOURCE NPTF / SLID information -]\n");
    printf("unk_dword_00: 0x%08X\n", nptf->unk_dword_00);
    printf("nbentry: 0x%04X (%d)\n", nptf->nbentry, nptf->nbentry);
    if (nptf->entries) {
        for (i = 0; i < nptf->nbentry; i++) {
            if (nptf->entries[i] != NULL) {
                odv_image_info(nptf->entries[i]);
            }
        }
    }
    printf("[---------------------------------]\n");
}

void odv_resource_clean_nptf(struct ODVResourceNptf *nptf)
{
    int i;

    if (nptf == NULL)
        return;
    if (nptf->entries != NULL) {
        for (i = 0; i < nptf->nbentry; i++) {
            if (nptf->entries[i] != NULL) {
                odv_image_clean(nptf->entries[i]);
                nptf->entries[i] = NULL;
            }
        }
        free(nptf->entries);
    }
    free(nptf);
}