#ifndef OPENDV_RESOURCE_CUR_H
#define OPENDV_RESOURCE_CUR_H

#include "odv_resource.h"

#define CUR_SIGNATURE 0x20525543

struct ODVResourceCur
{
    unsigned int unk_dword_00;
    unsigned short unk_word_00;
    unsigned short unk_word_01;
    unsigned short unk_word_02;
    unsigned short unk_word_03;
    int nbentry;
    struct ODVImage **entries;
};

void *odv_resource_parse_cur(struct ODVResourceFile *rfile);
void odv_resource_cur_info(const struct ODVResourceCur *cur);
void odv_resource_clean_cur(struct ODVResourceCur *cur);

#endif /* OPENDV_RESOURCE_CUR_H */
