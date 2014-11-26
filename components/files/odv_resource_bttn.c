#include "odv_resource_bttn.h"

void *odv_resource_parse_bttn(struct ODVResourceFile *rfile)
{
    struct ODVResourceBttn *bttn = NULL;
    struct ODVImage *entry = NULL;
    unsigned int unk_dword_00;
    unsigned int unk_dword_01;
    int nbentry = 0;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &unk_dword_00, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_bttn - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &unk_dword_01, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_bttn - file read 4 failed\n");
        return NULL;
    }
    bttn = calloc(1, sizeof (struct ODVResourceBttn));
    if (bttn == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_bttn - calloc failed\n");
        return NULL;
    }
    bttn->unk_dword_00 = unk_dword_00;
    bttn->unk_dword_01 = unk_dword_01;
    for (i = 0; i < 4; i++) {
        if ((1 << i) & unk_dword_01)
            nbentry++;
    }
    bttn->nbentry = nbentry;
    bttn->entries = calloc(nbentry, sizeof (struct ODVImage*));
    if (bttn->entries == NULL) {
        free(bttn);
        fprintf(stderr, "[-] odv_resource_parse_bttn - calloc failed\n");
        return NULL;
    }
    for (i = 0; i < bttn->nbentry; i++) {
        entry = odv_image_parse(rfile->file);
        if (entry == NULL) {
            odv_resource_clean_bttn(bttn);
            return NULL;
        }
        bttn->entries[i] = entry;
    }
    return bttn;
}

void odv_resource_bttn_info(const struct ODVResourceBttn *bttn)
{
    int i;

    if (bttn == NULL)
        return;
    printf("[- ODV RESOURCE BTTN information -]\n");
    printf("unk_dword_00: 0x%08X\n", bttn->unk_dword_00);
    printf("nbentry: 0x%04X (%d)\n", bttn->nbentry, bttn->nbentry);
    if (bttn->entries) {
        for (i = 0; i < bttn->nbentry; i++) {
            if (bttn->entries[i] != NULL) {
                odv_image_info(bttn->entries[i]);
            }
        }
    }
    printf("[---------------------------------]\n");
}

void odv_resource_clean_bttn(struct ODVResourceBttn *bttn)
{
    int i;

    if (bttn == NULL)
        return;
    if (bttn->entries != NULL) {
        for (i = 0; i < bttn->nbentry; i++) {
            if (bttn->entries[i] != NULL) {
                odv_image_clean(bttn->entries[i]);
                bttn->entries[i] = NULL;
            }
        }
        free(bttn->entries);
    }
    free(bttn);
}