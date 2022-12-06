#include "odv_resource_nptf.h"

void *odv_resource_parse_nptf(struct ODVResourceFile *rfile)
{
    struct ODVResourceNptf *nptf = NULL;
    unsigned int useless;
    unsigned int nb_entry_bit;
    int nbentry = 0;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &useless, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_nptf - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &nb_entry_bit, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_nptf - file read 4 failed\n");
        return NULL;
    }
    nptf = calloc(1, sizeof (struct ODVResourceNptf));
    if (nptf == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_nptf - calloc failed\n");
        return NULL;
    }
    nptf->useless = useless;
    nptf->nb_entry_bit = nb_entry_bit;
    for (i = 0; i < 6; i++) {
        if ((1 << i) & nb_entry_bit)
            nbentry++;
    }
    nptf->nbentry = nbentry;
    nptf->imgmap = odv_imagemap_parse_nb(rfile->file, nptf->nbentry);
    if (nptf->imgmap == NULL) {
        free(nptf);
        return NULL;
    }
    return nptf;
}

void odv_resource_nptf_info(const struct ODVResourceNptf *nptf)
{
    if (nptf == NULL)
        return;
    printf("[- ODV RESOURCE NPTF / SLID information -]\n");
    printf("useless: 0x%08X\n", nptf->useless);
    printf("nb_entry_bit: 0x%08X\n", nptf->nb_entry_bit);
    printf("nbentry: 0x%04X (%d)\n", nptf->nbentry, nptf->nbentry);
    if (nptf->imgmap != NULL) {
        odv_imagemap_info(nptf->imgmap);
    }
    printf("[---------------------------------]\n");
}

void odv_resource_clean_nptf(struct ODVResourceNptf *nptf)
{
    if (nptf == NULL)
        return;
    if (nptf->imgmap != NULL)
        odv_imagemap_clean(nptf->imgmap);
    free(nptf);
}