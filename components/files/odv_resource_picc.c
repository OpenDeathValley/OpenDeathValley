#include "odv_resource_picc.h"

void *odv_resource_parse_picc(struct ODVResourceFile *rfile)
{
    struct ODVResourcePicc *picc = NULL;
    struct ODVResourcePiccEntry *entry = NULL;
    unsigned int unk_dword_00;
    int nbentry;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &unk_dword_00, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_picc - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &nbentry, 4);
    if (numberofbytesread != 4 || nbentry < 0) {
        fprintf(stderr, "[-] odv_resource_parse_picc - file read 4 failed\n");
        return NULL;
    }
    picc = calloc(1, sizeof (struct ODVResourcePicc));
    if (picc == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_picc - calloc failed\n");
        return NULL;
    }
    picc->unk_dword_00 = unk_dword_00;
    picc->nbentry = nbentry;
    picc->entries = calloc(nbentry, sizeof (struct ODVResourcePiccEntry*));
    for (i = 0; i < picc->nbentry; i++) {
        entry = odv_ressource_parse_picc_entry(rfile);
        if (entry == NULL) {
            odv_resource_clean_picc(picc);
            return NULL;
        }
        picc->entries[i] = entry;
    }
    return picc;
}

struct ODVResourcePiccEntry *odv_ressource_parse_picc_entry(struct ODVResourceFile *rfile)
{
    struct ODVResourcePiccEntry *entry = NULL;
    size_t numberofbytesread = 0;
    unsigned short width;
    unsigned short height;
    unsigned int type_compression;
    unsigned int data_size;
    unsigned char *buf = NULL;

    numberofbytesread = odv_file_read(rfile->file, &width, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_ressource_parse_picc_entry - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &height, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_ressource_parse_picc_entry - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &type_compression, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_ressource_parse_picc_entry - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &data_size, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_ressource_parse_picc_entry - file read 4 failed\n");
        return NULL;
    }
    buf = calloc(data_size, sizeof (char));
    if (buf == NULL) {
        fprintf(stderr, "[-] odv_ressource_parse_picc_entry - calloc failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, buf, data_size);
    if (numberofbytesread != data_size) {
        fprintf(stderr, "[-] odv_ressource_parse_picc_entry - file read %d failed\n", data_size);
        free(buf);
        return NULL;
    }
    entry = calloc(1, sizeof (struct ODVResourcePiccEntry));
    if (entry == NULL) {
        fprintf(stderr, "[-] odv_ressource_parse_picc_entry - calloc failed\n");
        free(buf);
        return NULL;
    }
    entry->width = width;
    entry->height = height;
    entry->type_compression = type_compression;
    entry->data_size = data_size;
    entry->buf = buf;
    return entry;
}

void odv_resource_picc_entry_info(const struct ODVResourcePiccEntry *entry)
{
    if (entry == NULL)
        return;
    printf("[- ODV RESOURCE PICC ENTRY information -]\n");
    printf("width : 0x%04X\n", entry->width);
    printf("height: 0x%04X\n", entry->height);
    printf("type_compression: 0x%08X\n", entry->type_compression);
    printf("data_size: 0x%08X\n", entry->data_size);
    printf("[---------------------------------]\n");
}

void odv_resource_picc_info(const struct ODVResourcePicc *picc)
{
    int i;

    if (picc == NULL)
        return;
    printf("[- ODV RESOURCE PICC information -]\n");
    printf("unk_dword_00: 0x%08X\n", picc->unk_dword_00);
    printf("nbentry: 0x%04X (%d)\n", picc->nbentry, picc->nbentry);
    if (picc->entries) {
        for (i = 0; i < picc->nbentry; i++) {
            if (picc->entries[i] != NULL) {
                odv_resource_picc_entry_info(picc->entries[i]);
            }
        }
    }
    printf("[---------------------------------]\n");
}

void odv_resource_clean_picc_entry(struct ODVResourcePiccEntry *entry)
{
    if (entry == NULL)
        return;
    if (entry->buf != NULL)
        free(entry->buf);
    free(entry);
}

void odv_resource_clean_picc(struct ODVResourcePicc *picc)
{
    int i;

    if (picc == NULL)
        return;
    if (picc->entries != NULL) {
        for (i = 0; i < picc->nbentry; i++) {
            if (picc->entries[i] != NULL) {
                odv_resource_clean_picc_entry(picc->entries[i]);
                picc->entries[i] = NULL;
            }
        }
        free(picc->entries);
    }
    free(picc);
}

/*void *odv_resource_parse_wave(struct ODVResourceFile *rfile)
{
    struct ODVResourceWave *wave = NULL;
    struct ODVResourceWaveEntry *entry = NULL;
    unsigned int unk_dword_00;
    short nbentry;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &unk_dword_00, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_wave - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &nbentry, 2);
    if (numberofbytesread != 2 || nbentry < 0) {
        fprintf(stderr, "[-] odv_resource_parse_wave - file read 2 failed\n");
        return NULL;
    }
    wave = calloc(1, sizeof (struct ODVResourceWave));
    if (wave == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_wave - calloc failed\n");
        return NULL;
    }
    wave->unk_dword_00 = unk_dword_00;
    wave->nbentry = nbentry;
    wave->entries = calloc(nbentry, sizeof (struct ODVResourceWaveEntry*));
    for (i = 0; i < wave->nbentry; i++) {
        entry = odv_ressource_parse_wave_entry(rfile);
        if (entry == NULL) {
            odv_resource_clean_wave(wave);
            return NULL;
        }
        wave->entries[i] = entry;
    }
    return wave;
}

struct ODVResourceWaveEntry *odv_ressource_parse_wave_entry(struct ODVResourceFile *rfile)
{
    struct ODVResourceWaveEntry *entry = NULL;
    size_t numberofbytesread = 0;
    unsigned short length;
    char *buf = NULL;

    numberofbytesread = odv_file_read(rfile->file, &length, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_ressource_parse_wave_entry - file read 2 failed\n");
        return NULL;
    }
    buf = calloc(length + 1, sizeof (char));
    if (buf == NULL) {
        fprintf(stderr, "[-] odv_ressource_parse_wave_entry - calloc failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, buf, length);
    if (numberofbytesread != length) {
        fprintf(stderr, "[-] odv_ressource_parse_wave_entry - file read %d failed\n", length);
        free(buf);
        return NULL;
    }
    entry = calloc(1, sizeof (struct ODVResourceWaveEntry));
    if (entry == NULL) {
        fprintf(stderr, "[-] odv_ressource_parse_wave_entry - calloc failed\n");
        free(buf);
        return NULL;
    }
    entry->length = length;
    entry->buf = buf;
    return entry;
}

void odv_resource_wave_info(const struct ODVResourceWave *wave)
{
    int i;

    if (wave == NULL)
        return;
    printf("[- ODV RESOURCE WAVE information -]\n");
    printf("unk_dword_00: 0x%08X\n", wave->unk_dword_00);
    printf("nbentry: 0x%04X (%d)\n", wave->nbentry, wave->nbentry);
    if (wave->entries != NULL) {
        for (i = 0; i < wave->nbentry; i++) {
            if (wave->entries[i] != NULL) {
                printf("(%d): %s\n", i, wave->entries[i]->buf);
            }
        }
    }

    printf("[---------------------------------]\n");
}

void odv_resource_clean_wave_entry(struct ODVResourceWaveEntry *entry)
{
    if (entry == NULL)
        return;
    entry->length = 0;
    if (entry->buf != NULL)
        free(entry->buf);
    entry->buf = NULL;
    free(entry);
}

void odv_resource_clean_wave(struct ODVResourceWave *wave)
{
    int i;

    if (wave == NULL)
        return;
    if (wave->entries != NULL) {
        for (i = 0; i < wave->nbentry; i++) {
            if (wave->entries[i] != NULL) {
                odv_resource_clean_wave_entry(wave->entries[i]);
                wave->entries[i] = NULL;
            }
        }
        free(wave->entries);
    }
    free(wave);
}*/