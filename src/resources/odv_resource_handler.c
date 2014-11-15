#include "odv_resource_handler.h"

struct ODVResourceFile *odv_resource_open(const char *filename)
{
    struct ODVFile *file = NULL;
    struct ODVResourceFile *rfile = NULL;
    struct ODVResourceEntry *entry = NULL;
    int i;

    file = odv_file_open(filename);
    if (file == NULL) {
        fprintf(stderr, "[-] odv_open_resource - odv_file_open failed\n");
        return NULL;
    }
    rfile = calloc(1, sizeof (struct ODVResourceFile));
    if (rfile == NULL) {
        fprintf(stderr, "[-] odv_open_resource - calloc failed\n");
        odv_file_close(file);
        return NULL;
    }
    rfile->file = file;
    if (odv_resource_read_header(rfile) == 0) {
        odv_file_close(file);
        free(rfile);
        return NULL;
    }
    rfile->entries = calloc(rfile->nbtypeentry, sizeof(struct ODVResourceEntry *));
    if (rfile->entries == NULL) {
        fprintf(stderr, "[-] odv_resource_open - calloc failed\n");
        odv_resource_close(rfile);
        return NULL;
    }
    for (i = 0; i < rfile->nbtypeentry; i++) {
        entry = odv_resource_parse_entry(rfile);
        if (entry == NULL) {
            odv_resource_close(rfile);
            return NULL;
        }
        rfile->entries[i] = entry;
    }
    return rfile;
}

int odv_resource_read_header(struct ODVResourceFile *rfile)
{
    size_t numberofbytesread = 0;

    numberofbytesread = odv_file_read(rfile->file, &rfile->signature, 4);
    if (numberofbytesread != 4 || rfile->signature != RESOURCE_SIGNATURE) {
        fprintf(stderr, "[-] odv_resource_read_header - wrong resource signature\n");
        return 0;
    }
    numberofbytesread = odv_file_read(rfile->file, &rfile->version, 4);
    if (numberofbytesread != 4 || rfile->version != RESOURCE_VERSION) {
        fprintf(stderr, "[-] odv_resource_read_header - wrong resource version\n");
        return 0;
    }
    numberofbytesread = odv_file_read(rfile->file, &rfile->nbtypeentry, 4);
    if (numberofbytesread != 4 || rfile->nbtypeentry == 0) {
        fprintf(stderr, "[-] odv_resource_read_header - wrong number of type entry\n");
        return 0;
    }
    return 1;
}

struct ODVResourceEntry *odv_resource_parse_entry(struct ODVResourceFile *rfile)
{
    unsigned int signature;
    unsigned int index;
    size_t numberofbytesread = 0;
    struct ODVResourceEntry *entry = NULL;

    numberofbytesread = odv_file_read(rfile->file, &signature, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_entry - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &index, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_entry - file read 4 failed\n");
        return NULL;
    }
    entry = calloc(1, sizeof (struct ODVResourceEntry));
    if (entry == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_entry - calloc failed\n");
        return NULL;
    }
    entry->signature = signature;
    entry->index = index;
    switch (signature) {
        case WAVE_SIGNATURE:
            entry->data = odv_resource_parse_wave(rfile);
            if (entry->data == NULL) {
                free(entry);
                entry = NULL;
            }
        break;

        case TEXT_SIGNATURE:
            entry->data = odv_resource_parse_text(rfile);
            if (entry->data == NULL) {
                free(entry);
                entry = NULL;
            }
        break;

        default:
            fprintf(stderr, "[-] odv_resource_parse_entry - unknow signature %08X\n", signature);
            free(entry);
            entry = NULL;
    }
    return entry;
}

/*int odv_resource_get_type_index(struct ODVResourceFile *rfile, unsigned int index)
{
    if (rfile == NULL)
        return 0;
    return 1;
}*/

void odv_resource_close(struct ODVResourceFile *rfile)
{
    int i;

    if (rfile == NULL)
        return;
    if (rfile->file != NULL)
        odv_file_close(rfile->file);
    if (rfile->entries != NULL) {
        for (i = 0; i < rfile->nbtypeentry; i++) {
            if (rfile->entries[i] != NULL) {
                switch (rfile->entries[i]->signature) {
                    case WAVE_SIGNATURE:
                        odv_resource_clean_wave(rfile->entries[i]->data);
                        free(rfile->entries[i]);
                        rfile->entries[i] = NULL;
                    break;

                    case TEXT_SIGNATURE:
                        odv_resource_clean_text(rfile->entries[i]->data);
                        free(rfile->entries[i]);
                        rfile->entries[i] = NULL;
                    break;

                    default:
                        fprintf(stderr, "[-] odv_resource_close - unknow signature %08X\n", rfile->entries[i]->signature);
                }
            }
        }
        free(rfile->entries);
    }
    free(rfile);
}

void odv_resource_info(const struct ODVResourceFile *rfile)
{
    int i;

    if (rfile == NULL)
        return;
    odv_file_info(rfile->file);
    printf("[- ODV resource header information -]\n");
    printf("Signature   : 0x%08X\n", rfile->signature);
    printf("Version     : 0x%08X\n", rfile->version);
    printf("NbTypeEntry : 0x%08X\n", rfile->nbtypeentry);
    if (rfile->entries != NULL) {
        for (i = 0; i < rfile->nbtypeentry; i++) {
            if (rfile->entries[i] != NULL) {
                switch (rfile->entries[i]->signature) {
                    case WAVE_SIGNATURE:
                        odv_resource_wave_info(rfile->entries[i]->data);
                        break;

                    case TEXT_SIGNATURE:
                        odv_resource_text_info(rfile->entries[i]->data);
                        break;

                    default:
                        fprintf(stderr, "[-] odv_resource_close - unknow signature %08X\n", rfile->entries[i]->signature);
                }
            }
        }
    }
    printf("[-----------------------------------]\n");
    /* odv_resource_headerinfo(&rfile->header); */
}

/*void odv_resource_headerinfo(const struct ODVResourceHeader *re)
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
}*/