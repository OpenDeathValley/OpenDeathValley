#ifndef OPENDV_RESOURCE_NPTF_H
#define OPENDV_RESOURCE_NPTF_H

#include "odv_resource.h"

#define NPTF_SIGNATURE 0x4654504E
#define SLID_SIGNATURE 0x44494C53

struct ODVResourceNptf
{
    unsigned int unk_dword_00;
    unsigned int unk_dword_01;
    int nbentry;
    struct ODVImage **entries;
};

void *odv_resource_parse_nptf(struct ODVResourceFile *rfile);
void odv_resource_nptf_info(const struct ODVResourceNptf *nptf);
void odv_resource_clean_nptf(struct ODVResourceNptf *nptf);

#endif /* OPENDV_RESOURCE_NPTF_H */
