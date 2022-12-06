#ifndef OPENDV_RESOURCE_TOGL_H
#define OPENDV_RESOURCE_TOGL_H

#include "odv_resource.h"

#define TOGL_SIGNATURE 0x4C474F54

struct ODVResourceTogl
{
    unsigned int useless;
    unsigned int nb_entry_bit;
    int nbentry;
    struct ODVImageMap *imgmap;
};

void *odv_resource_parse_togl(struct ODVResourceFile *rfile);
void odv_resource_togl_info(const struct ODVResourceTogl *togl);
void odv_resource_clean_togl(struct ODVResourceTogl *togl);

#endif /* OPENDV_RESOURCE_TOGL_H */
