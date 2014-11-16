#ifndef OPENDV_FXG_HANDLER_H
#define OPENDV_FXG_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "odv_file.h"

#define FXG_SIGNATURE 0x4B425846

struct ODVSoundFXGEntry
{
    unsigned int unk_dword_00;
};

struct ODVSoundFXGFile
{
    struct ODVFile *file;
    /* HEADER */
    unsigned int signature;
    unsigned int unk_dword_00;
    unsigned int unk_dword_01;
    int nbentry;

    struct ODVSoundFXGEntry **entries;
};

struct ODVSoundFXGFile *odv_fxg_open(const char *filename);
int odv_fxg_parse_header(struct ODVSoundFXGFile *sfile);
struct ODVSoundFXGEntry *odv_fxg_parse_entry(struct ODVSoundFXGFile *sfile);
void odv_fxg_clean_entry(struct ODVSoundFXGEntry *entry);
void odv_fxg_close(struct ODVSoundFXGFile *sfile);

#endif /* OPENDV_FXG_HANDLER_H */