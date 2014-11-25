#include "odv_resource_togl.h"

void *odv_resource_parse_togl(struct ODVResourceFile *rfile)
{
    struct ODVResourceTogl *togl = NULL;
    struct ODVResourceToglEntry *entry = NULL;
    unsigned int unk_dword_00;
    unsigned int unk_dword_01;
    int nbentry = 0;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &unk_dword_00, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_togl - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &unk_dword_01, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_togl - file read 4 failed\n");
        return NULL;
    }
    togl = calloc(1, sizeof (struct ODVResourceTogl));
    if (togl == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_togl - calloc failed\n");
        return NULL;
    }
    togl->unk_dword_00 = unk_dword_00;
    togl->unk_dword_01 = unk_dword_01;
    for (i = 0; i < 5; i++) {
        if ((1 << i) & unk_dword_01)
            nbentry++;
    }
    togl->nbentry = nbentry;
    togl->entries = calloc(nbentry, sizeof (struct ODVResourceToglEntry*));
    for (i = 0; i < togl->nbentry; i++) {
        entry = odv_ressource_parse_togl_entry(rfile);
        if (entry == NULL) {
            odv_resource_clean_togl(togl);
            return NULL;
        }
        togl->entries[i] = entry;
    }
    return togl;
}

struct ODVResourceToglEntry *odv_ressource_parse_togl_entry(struct ODVResourceFile *rfile)
{
    struct ODVResourceToglEntry *entry = NULL;
    size_t numberofbytesread = 0;
    unsigned short width;
    unsigned short height;
    unsigned int type_compression;
    unsigned int data_size;
    unsigned char *buf = NULL;

    numberofbytesread = odv_file_read(rfile->file, &width, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_ressource_parse_togl_entry - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &height, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_ressource_parse_togl_entry - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &type_compression, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_ressource_parse_togl_entry - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &data_size, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_ressource_parse_togl_entry - file read 4 failed\n");
        return NULL;
    }
    buf = calloc(data_size, sizeof (char));
    if (buf == NULL) {
        fprintf(stderr, "[-] odv_ressource_parse_togl_entry - calloc failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, buf, data_size);
    if (numberofbytesread != data_size) {
        fprintf(stderr, "[-] odv_ressource_parse_togl_entry - file read %d failed\n", data_size);
        free(buf);
        return NULL;
    }
    entry = calloc(1, sizeof (struct ODVResourceToglEntry));
    if (entry == NULL) {
        fprintf(stderr, "[-] odv_ressource_parse_togl_entry - calloc failed\n");
        free(buf);
        return NULL;
    }
    entry->width = width;
    entry->height = height;
    entry->type_compression = type_compression;
    entry->data_size = data_size;
    entry->buf = buf;
    return entry;
}

void odv_resource_togl_entry_info(const struct ODVResourceToglEntry *entry)
{
    if (entry == NULL)
        return;
    printf("[- ODV RESOURCE TOGL ENTRY information -]\n");
    printf("width : 0x%04X\n", entry->width);
    printf("height: 0x%04X\n", entry->height);
    printf("type_compression: 0x%08X\n", entry->type_compression);
    printf("data_size: 0x%08X\n", entry->data_size);
    printf("[---------------------------------]\n");
}

void odv_resource_togl_info(const struct ODVResourceTogl *togl)
{
    int i;

    if (togl == NULL)
        return;
    printf("[- ODV RESOURCE TOGL information -]\n");
    printf("unk_dword_00: 0x%08X\n", togl->unk_dword_00);
    printf("nbentry: 0x%04X (%d)\n", togl->nbentry, togl->nbentry);
    if (togl->entries) {
        for (i = 0; i < togl->nbentry; i++) {
            if (togl->entries[i] != NULL) {
                odv_resource_togl_entry_info(togl->entries[i]);
            }
        }
    }
    printf("[---------------------------------]\n");
}

void odv_resource_clean_togl_entry(struct ODVResourceToglEntry *entry)
{
    if (entry == NULL)
        return;
    if (entry->buf != NULL)
        free(entry->buf);
    free(entry);
}

void odv_resource_clean_togl(struct ODVResourceTogl *togl)
{
    int i;

    if (togl == NULL)
        return;
    if (togl->entries != NULL) {
        for (i = 0; i < togl->nbentry; i++) {
            if (togl->entries[i] != NULL) {
                odv_resource_clean_togl_entry(togl->entries[i]);
                togl->entries[i] = NULL;
            }
        }
        free(togl->entries);
    }
    free(togl);
}