#include "odv_resource_handler.h"

struct ODVResourceFile *odv_resource_open(const char *filename)
{
    struct ODVFile *file = NULL;
    struct ODVResourceFile *rfile = NULL;

    file = odv_file_open(filename);
    if (file == NULL) {
        fprintf(stderr, "[-] odv_open_resource - odv_file_open failed\n");
        return NULL;
    }
    rfile = (struct ODVResourceFile*)malloc(sizeof (struct ODVResourceFile));
    if (rfile == NULL) {
        fprintf(stderr, "[-] odv_open_resource - malloc failed\n");
        odv_file_close(file);
        return NULL;
    }
    memset(rfile, 0, sizeof (struct ODVResourceFile));
    rfile->file = file;
    if (odv_resource_read_header(rfile) == 0) {
        odv_file_close(file);
        free(rfile);
        rfile = NULL;
    }
    return rfile;
}

int odv_resource_read_header(struct ODVResourceFile *rfile)
{
    size_t numberofbytesread = 0;

    numberofbytesread = odv_file_read(rfile->file, &rfile->header.signature, 4);
    if (numberofbytesread != 4 || rfile->header.signature != RESOURCE_SIGNATURE) {
        fprintf(stderr, "[-] odv_resource_read_header - wrong resource signature\n");
        return 0;
    }
    numberofbytesread = odv_file_read(rfile->file, &rfile->header.version, 4);
    if (numberofbytesread != 4 || rfile->header.version != RESOURCE_VERSION) {
        fprintf(stderr, "[-] odv_resource_read_header - wrong resource version\n");
        return 0;
    }
    numberofbytesread = odv_file_read(rfile->file, &rfile->header.nbtypeentry, 4);
    if (numberofbytesread != 4 || rfile->header.nbtypeentry == 0) {
        fprintf(stderr, "[-] odv_resource_read_header - wrong number of type entry\n");
        return 0;
    }
    return 1;
}

/*int odv_resource_get_type_index(struct ODVResourceFile *rfile, unsigned int index)
{
    if (rfile == NULL)
        return 0;
    return 1;
}*/

void odv_resource_close(struct ODVResourceFile *rfile)
{
    unsigned int i;

    if (rfile == NULL)
        return;
    if (rfile->file != NULL)
        odv_file_close(rfile->file);
    if (rfile->type != NULL) {
        for (i = 0; i < rfile->header.nbtypeentry; i++) {
            if (rfile->type[i] != NULL)
                free(rfile->type[i]);
        }
        free(rfile->type);
    }
    free(rfile);
}

void odv_resource_info(const struct ODVResourceFile *rfile)
{
    if (rfile == NULL)
        return;
    odv_file_info(rfile->file);
    odv_resource_headerinfo(&rfile->header);
}

void odv_resource_headerinfo(const struct ODVResourceHeader *re)
{
    if (re == NULL)
        return;
    printf("[- ODV resource header information -]\n");
    printf("Signature   : 0x%08X\n", re->signature);
    printf("Version     : 0x%08X\n", re->version);
    printf("NbTypeEntry : 0x%08X\n", re->nbtypeentry);
    printf("[-----------------------------------]\n");
}

void odv_resourcetype_headerinfo(const struct ODVResourceTypeHeader *re)
{
    if (re == NULL)
        return;
    printf("[- ODV resource type header information -]\n");
    printf("Signature : 0x%08X\n", re->signature);
    printf("Index     : 0x%08X\n", re->index);
    printf("[----------------------------------------]\n");
}
