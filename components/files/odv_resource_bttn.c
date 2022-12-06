#include "odv_resource_bttn.h"

void *odv_resource_parse_bttn(struct ODVResourceFile *rfile)
{
    struct ODVResourceBttn *bttn = NULL;
    unsigned int useless;
    unsigned int nb_entry_bit;
    int nbentry = 0;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &useless, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_bttn - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &nb_entry_bit, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_bttn - file read 4 failed\n");
        return NULL;
    }
    bttn = calloc(1, sizeof (struct ODVResourceBttn));
    if (bttn == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_bttn - calloc failed\n");
        return NULL;
    }
    bttn->useless = useless;
    bttn->nb_entry_bit = nb_entry_bit;
    for (i = 0; i < 4; i++) {
        if ((1 << i) & nb_entry_bit)
            nbentry++;
    }
    bttn->nbentry = nbentry;
    bttn->imgmap = odv_imagemap_parse_nb(rfile->file, bttn->nbentry);
    if (bttn->imgmap == NULL) {
        free(bttn);
        return NULL;
    }
    return bttn;
}

void odv_resource_bttn_info(const struct ODVResourceBttn *bttn)
{
    if (bttn == NULL)
        return;
    printf("[- ODV RESOURCE BTTN information -]\n");
    printf("useless: 0x%08X\n", bttn->useless);
    printf("nb_entry_bit: 0x%08X\n", bttn->nb_entry_bit);
    printf("nbentry: 0x%04X (%d)\n", bttn->nbentry, bttn->nbentry);
    if (bttn->imgmap != NULL) {
        odv_imagemap_info(bttn->imgmap);
    }
    printf("[---------------------------------]\n");
}

void odv_resource_clean_bttn(struct ODVResourceBttn *bttn)
{
    if (bttn == NULL)
        return;
    if (bttn->imgmap != NULL)
        odv_imagemap_clean(bttn->imgmap);
    free(bttn);
}