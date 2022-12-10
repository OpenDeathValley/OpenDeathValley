#ifndef OPENDV_RESOURCE_PICC_H
#define OPENDV_RESOURCE_PICC_H

#include "odv_resource.h"

#define PICC_SIGNATURE 0x43434950

#define PIC_SIGNATURE 0x20434950

struct ODVResourcePicc
{
    unsigned int useless;
    int nbentry;
    struct ODVImageMap *imgmap;
};

void *odv_resource_parse_picc(struct ODVResourceFile *rfile);
void *odv_resource_parse_pic(struct ODVResourceFile *rfile);
void odv_resource_picc_info(const struct ODVResourcePicc *picc);
void odv_resource_picc_extract(const struct ODVResourcePicc *picc, const char *filename, const char *output, unsigned int id);
void odv_resource_clean_picc(struct ODVResourcePicc *picc);

#endif /* OPENDV_RESOURCE_PICC_H */
