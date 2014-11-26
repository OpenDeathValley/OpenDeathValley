#ifndef OPENDV_RESOURCE_RDO_H
#define OPENDV_RESOURCE_RDO_H

#include "odv_resource.h"

#define RDO_SIGNATURE 0x204F4452

struct ODVResourceRdo
{
    unsigned int unk_dword_00;
    unsigned int unk_dword_01;
    int nbentry;
    struct ODVImage **entries;
};

void *odv_resource_parse_rdo(struct ODVResourceFile *rfile);
void odv_resource_rdo_info(const struct ODVResourceRdo *rdo);
void odv_resource_clean_rdo(struct ODVResourceRdo *rdo);

#endif /* OPENDV_RESOURCE_RDO_H */
