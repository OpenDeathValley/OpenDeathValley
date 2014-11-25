#ifndef OPENDV_RESOURCE_TOGL_H
#define OPENDV_RESOURCE_TOGL_H

#include "odv_resource.h"

#define TOGL_SIGNATURE 0x4C474F54

struct ODVResourceToglEntry
{
    unsigned short width;
    unsigned short height;
    unsigned int type_compression;
    unsigned int data_size;
    unsigned char *buf;
};

struct ODVResourceTogl
{
    unsigned int unk_dword_00;
    unsigned int unk_dword_01;
    int nbentry;
    struct ODVResourceToglEntry **entries;
};

void *odv_resource_parse_togl(struct ODVResourceFile *rfile);
struct ODVResourceToglEntry *odv_ressource_parse_togl_entry(struct ODVResourceFile *rfile);
void odv_resource_togl_info(const struct ODVResourceTogl *togl);
void odv_resource_togl_entry_info(const struct ODVResourceToglEntry *entry);
void odv_resource_clean_togl(struct ODVResourceTogl *togl);

#endif /* OPENDV_RESOURCE_TOGL_H */
