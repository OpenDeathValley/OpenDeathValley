#ifndef OPENDV_RESOURCE_TEXT_H
#define OPENDV_RESOURCE_TEXT_H

#include "odv_resource.h"

#define TEXT_SIGNATURE 0x54584554

struct ODVResourceTextEntry
{
    unsigned short length;
    char *buf;
};

struct ODVResourceText
{
    unsigned int unk_dword_00;
    short nbentry;
    struct ODVResourceTextEntry **entries;
};

void *odv_resource_parse_text(struct ODVResourceFile *rfile);

struct ODVResourceTextEntry *odv_ressource_parse_text_entry(struct ODVResourceFile *rfile);

void odv_resource_clean_text(struct ODVResourceText *text);
void odv_resource_text_info(const struct ODVResourceText *text);

#endif /* OPENDV_RESOURCE_TEXT_H */
