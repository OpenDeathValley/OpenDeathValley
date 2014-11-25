#ifndef OPENDV_RESOURCE_PICC_H
#define OPENDV_RESOURCE_PICC_H

#include "odv_resource.h"

#define PICC_SIGNATURE 0x43434950

/*struct ODVResourceWaveEntry
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
void odv_resource_wave_info(const struct ODVResourceWave *wave);*/

struct ODVResourcePiccEntry
{
    unsigned short width;
    unsigned short height;
    unsigned int type_compression;
    unsigned int data_size;
    unsigned char *buf;
};

struct ODVResourcePicc
{
    unsigned int unk_dword_00;
    int nbentry;
    struct ODVResourcePiccEntry **entries;
};

void *odv_resource_parse_picc(struct ODVResourceFile *rfile);
struct ODVResourcePiccEntry *odv_ressource_parse_picc_entry(struct ODVResourceFile *rfile);
void odv_resource_picc_info(const struct ODVResourcePicc *picc);
void odv_resource_picc_entry_info(const struct ODVResourcePiccEntry *entry);
void odv_resource_clean_picc(struct ODVResourcePicc *picc);

#endif /* OPENDV_RESOURCE_PICC_H */
