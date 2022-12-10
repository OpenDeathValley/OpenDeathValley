#include "odv_dvm_handler.h"

struct ODVDvm *odv_dvm_open(const char *filename)
{
    struct ODVFile *file = NULL;
    struct ODVDvm *dvm = NULL;

    file = odv_file_open(filename);
    if (file == NULL) {
        fprintf(stderr, "[-] odv_dvm_open - odv_file_open failed\n");
        return NULL;
    }
    dvm = calloc(1, sizeof (struct ODVDvm));
    if (dvm == NULL) {
        fprintf(stderr, "[-] odv_dvm_open - calloc failed\n");
        odv_file_close(file);
        return NULL;
    }
    dvm->file = file;
    dvm->imgmap = odv_imagemap_parse_one(dvm->file);
    if (dvm->imgmap == NULL) {
        odv_dvm_close(dvm);
        return NULL;
    }
    return dvm;
}

void odv_dvm_info(const struct ODVDvm *dvm)
{
    if (dvm == NULL)
        return;
    printf("[- ODV DVM information -]\n");
    odv_imagemap_info(dvm->imgmap);
    printf("[---------------------------------]\n");
}

void odv_dvm_close(struct ODVDvm *dvm)
{
    if (dvm == NULL) {
        return;
    }
    if (dvm->file != NULL) {
        odv_file_close(dvm->file);
    }
    if (dvm->imgmap != NULL) {
        odv_imagemap_clean(dvm->imgmap);
    }
    free(dvm);
}