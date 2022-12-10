#ifndef OPENDV_FNT_HANDLER_H
#define OPENDV_FNT_HANDLER_H

#include <stdlib.h>
#include <stdio.h>

#include "odv_file.h"
#include "odv_imagemap.h"

#define FNT_SIGNATURE "\x53\x42\x46\x4F\x4E\x54" // "SBFONT"

#pragma pack(push, 1)
struct ODVFntChar
{
    unsigned short value;
    unsigned int coordinate_y;
    unsigned int width;
    unsigned int pre_spacing;
    unsigned int post_spacing;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ODVFntHeader
{
    char signature[6];
    unsigned int version;
    char font_name[36];
    unsigned int type;
    unsigned int height;
    unsigned int unk_dword_02;  // Width rectangle letter
    unsigned int unk_dword_03;  // Maximum width letter
    unsigned int nb_entry;
};
#pragma pack(pop)

struct ODVFnt
{
    struct ODVFile *file;
    struct ODVFntHeader header;

    /* if header.version >= 0x200 */
    unsigned int unk_dword_00;

    struct ODVFntChar **char_entries;
    struct ODVImageMap *imgmap;
};

struct ODVFnt *odv_fnt_open(const char *filename);
int odv_fnt_parse_header(struct ODVFnt *fnt);
struct ODVFntChar *odv_fnt_parse_entry(struct ODVFnt *fnt);
void odv_fnt_info(const struct ODVFnt *fnt);
void odv_fnt_close(struct ODVFnt *fnt);

#endif /* OPENDV_FNT_HANDLER_H */
