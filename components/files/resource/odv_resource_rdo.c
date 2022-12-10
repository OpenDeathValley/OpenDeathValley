#include "odv_resource_rdo.h"

void *odv_resource_parse_rdo(struct ODVResourceFile *rfile)
{
    struct ODVResourceRdo *rdo = NULL;
    unsigned int useless;
    unsigned int nb_entry_bit;
    int nbentry = 0;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &useless, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_rdo - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &nb_entry_bit, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_rdo - file read 4 failed\n");
        return NULL;
    }
    rdo = calloc(1, sizeof (struct ODVResourceRdo));
    if (rdo == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_rdo - calloc failed\n");
        return NULL;
    }
    rdo->useless = useless;
    rdo->nb_entry_bit = nb_entry_bit;
    for (i = 0; i < 7; i++) {
        if ((1 << i) & nb_entry_bit)
            nbentry++;
    }
    rdo->nbentry = nbentry;
    rdo->imgmap = odv_imagemap_parse_nb(rfile->file, rdo->nbentry);
    if (rdo->imgmap == NULL) {
        free(rdo);
        return NULL;
    }
    return rdo;
}

void odv_resource_rdo_info(const struct ODVResourceRdo *rdo)
{
    if (rdo == NULL)
        return;
    printf("[- ODV RESOURCE RDO information -]\n");
    printf("useless: 0x%08X\n", rdo->useless);
    printf("nb_entry_bit: 0x%08X\n", rdo->nb_entry_bit);
    printf("nbentry: 0x%04X (%d)\n", rdo->nbentry, rdo->nbentry);
    if (rdo->imgmap != NULL) {
        odv_imagemap_info(rdo->imgmap);
    }
    printf("[---------------------------------]\n");
}

void odv_resource_rdo_extract(const struct ODVResourceRdo *picc, const char *filename, const char *output, unsigned int id)
{
    char suffix[256];

    snprintf(suffix, sizeof (suffix) - 1, "%d", id);

    odv_imagemap_extract(picc->imgmap, filename, output, suffix);
}

void odv_resource_clean_rdo(struct ODVResourceRdo *rdo)
{
    if (rdo == NULL)
        return;
    if (rdo->imgmap != NULL)
        odv_imagemap_clean(rdo->imgmap);
    free(rdo);
}