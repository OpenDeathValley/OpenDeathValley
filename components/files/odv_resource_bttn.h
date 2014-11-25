#ifndef OPENDV_RESOURCE_BTTN_H
#define OPENDV_RESOURCE_BTTN_H

#include "odv_resource.h"

#define BTTN_SIGNATURE 0x4E545442

struct ODVResourceBttn
{
    unsigned int unk_dword_00;
    unsigned int unk_dword_01;
    int nbentry;
    struct ODVImage **entries;
};

void *odv_resource_parse_bttn(struct ODVResourceFile *rfile);
void odv_resource_bttn_info(const struct ODVResourceBttn *bttn);
void odv_resource_clean_bttn(struct ODVResourceBttn *bttn);

#endif /* OPENDV_RESOURCE_BTTN_H */
