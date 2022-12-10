#ifndef OPENDV_RESOURCE_NPTF_H
#define OPENDV_RESOURCE_NPTF_H

#include "odv_resource.h"

#define NPTF_SIGNATURE 0x4654504E
#define SLID_SIGNATURE 0x44494C53

struct ODVResourceNptf
{
    unsigned int useless;
    unsigned int nb_entry_bit;
    int nbentry;
    struct ODVImageMap *imgmap;
};

void *odv_resource_parse_nptf(struct ODVResourceFile *rfile);
void odv_resource_nptf_info(const struct ODVResourceNptf *nptf);
void odv_resource_nptf_extract(const struct ODVResourceNptf *picc, const char *filename, const char *output, unsigned int id);
void odv_resource_clean_nptf(struct ODVResourceNptf *nptf);

#endif /* OPENDV_RESOURCE_NPTF_H */
