#ifndef OPENDV_MAP_HANDLER_H
#define OPENDV_MAP_HANDLER_H

#include <stdlib.h>
#include <stdio.h>

#include "odv_file.h"
#include "odv_imagemap.h"

struct ODVMap
{
    struct ODVFile *file;
    struct ODVImageMap *imgmap;
};

struct ODVMap *odv_map_open(const char *filename);
void odv_map_info(const struct ODVMap *mfile);
void odv_map_close(struct ODVMap *mfile);

#endif /* OPENDV_MAP_HANDLER_H */
