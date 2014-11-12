#ifndef OPENDV_RESOURCE_MANAGER_H
#define OPENDV_RESOURCE_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "odv_file.h"

#define RESOURCE_SIGNATURE 0x53455253
#define RESOURCE_VERSION 0x00000100

#define RESOURCE_HEADER_SIZE 0x0C

struct ODVResourceHeader
{
    unsigned int signature;
    unsigned int version;
    unsigned int nbtypeentry;
};

struct ODVResourceTypeHeader
{
    unsigned int signature;
    unsigned int index;
};

struct ODVResourceType
{
    struct ODVResourceTypeHeader header;
    void *data;
};

struct ODVResourceFile
{
    struct ODVFile *file;
    struct ODVResourceHeader header;
    struct ODVResourceType **type;
};

struct ODVResourceFile *odv_resource_open(const char *filename);
int odv_resource_read_header(struct ODVResourceFile *rfile);
void odv_resource_close(struct ODVResourceFile *rfile);

int odv_resource_get_type_index(struct ODVResourceFile *rfile, unsigned int index);

/* INFO / DBG */

void odv_resource_info(const struct ODVResourceFile *rfile);
void odv_resource_headerinfo(const struct ODVResourceHeader *re);
void odv_resourcetype_headerinfo(const struct ODVResourceTypeHeader *re);

#endif /* OPENDV_RESSOURCE_MANAGER_H */
