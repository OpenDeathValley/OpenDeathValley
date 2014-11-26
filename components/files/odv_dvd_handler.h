#ifndef OPENDV_DVD_HANDLER_H
#define OPENDV_DVD_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "odv_file.h"
#include "odv_image.h"

#define MISC_SIGNATURE 0x4353494D
#define BGND_SIGNATURE 0x444E4742

#pragma pack(push, 1)
struct ODVDvdMisc
{
    unsigned char unk_byte_00;
    unsigned short unk_word_00;
    unsigned short unk_word_01;
    unsigned int unk_dword_00;
    unsigned int unk_dword_01;
    unsigned int unk_dword_02;
    unsigned char unk_byte_01;
    unsigned short unk_word_02;
    unsigned int unk_dword_03;
    unsigned char unk_byte_02;
    unsigned char unk_byte_03;
    unsigned int unk_dword_04;
    unsigned char unk_byte_04;
    unsigned short unk_word_04;
    unsigned short unk_word_05;
};
#pragma pack(pop)

struct ODVDvdBgnd
{
    unsigned int signature;
    unsigned char *filename;    /* .dvm */
    struct ODVImage *img;
};

struct ODVDDvdEntry
{
    unsigned int signature;
    void *data;
};

struct ODVDDvdFile
{
    struct ODVFile *file;
    unsigned int nbentry;
    struct ODVDDvdEntry **entries;
};

struct ODVDDvdFile *odv_dvd_open(const char *filename);
int odv_dvd_parse(struct ODVDDvdFile *dfile);
int odv_dvd_parse_entry(struct ODVDDvdFile *dfile);

void *odv_dvd_parse_misc(struct ODVDDvdFile *misc);
void odv_dvd_misc_info(const struct ODVDvdMisc *misc);
void odv_dvd_clean_misc(struct ODVDvdMisc *misc);

void *odv_dvd_parse_bgnd(struct ODVDDvdFile *dfile);
void odv_dvd_bgnd_info(const struct ODVDvdBgnd *bgnd);
void odv_dvd_clean_bgnd(struct ODVDvdBgnd *bgnd);

void odv_dvd_info(struct ODVDDvdFile *dfile);


void odv_dvd_close(struct ODVDDvdFile *dfile);

#endif /* OPENDV_DVD_HANDLER_H */
