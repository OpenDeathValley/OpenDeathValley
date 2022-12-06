#ifndef OPENDV_RESOURCE_H
#define OPENDV_RESOURCE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "odv_file.h"
#include "odv_utils.h"
#include "odv_imagemap.h"

#define RESOURCE_SIGNATURE 0x53455253
#define RESOURCE_VERSION 0x00000100

#define RESOURCE_HEADER_SIZE 0x0C

struct ODVResourceEntry
{
    unsigned int signature;
    unsigned int index;
    void *data;
};

struct ODVResourceFile
{
    struct ODVFile *file;

    /* HEADER */
    unsigned int signature;
    unsigned int version;
    int nbtypeentry;

    struct ODVResourceEntry **entries;
};

#endif /* OPENDV_RESOURCE_HANDLER_H */
