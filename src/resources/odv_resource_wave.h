#ifndef OPENDV_RESOURCE_WAVE_H
#define OPENDV_RESOURCE_WAVE_H

#include "odv_resource.h"

#define WAVE_SIGNATURE 0x45564157

struct ODVResourceWaveEntry
{
    unsigned short length;
    char *buf;
};

struct ODVResourceWave
{
    unsigned int unk_dword_00;
    short nbentry;
    struct ODVResourceWaveEntry **entries;
};

void *odv_resource_parse_wave(struct ODVResourceFile *rfile);
struct ODVResourceWaveEntry *odv_ressource_parse_wave_entry(struct ODVResourceFile *rfile);
void odv_resource_clean_wave(struct ODVResourceWave *wave);
void odv_resource_wave_info(const struct ODVResourceWave *wave);

#endif /* OPENDV_RESOURCE_WAVE_H */
