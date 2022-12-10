#ifndef OPENDV_RESOURCE_RDO_H
#define OPENDV_RESOURCE_RDO_H

#include "odv_resource.h"

#define RDO_SIGNATURE 0x204F4452

struct ODVResourceRdo
{
    unsigned int useless;
    unsigned int nb_entry_bit;
    int nbentry;
    struct ODVImageMap *imgmap;
};

void *odv_resource_parse_rdo(struct ODVResourceFile *rfile);
void odv_resource_rdo_info(const struct ODVResourceRdo *rdo);
void odv_resource_rdo_extract(const struct ODVResourceRdo *picc, const char *filename, const char *output, unsigned int id);
void odv_resource_clean_rdo(struct ODVResourceRdo *rdo);

#endif /* OPENDV_RESOURCE_RDO_H */
