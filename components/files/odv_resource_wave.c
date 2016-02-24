#include "odv_resource_wave.h"

void *odv_resource_parse_wave(struct ODVResourceFile *rfile)
{
    struct ODVResourceWave *wave = NULL;
    struct ODVResourceWaveEntry *entry = NULL;
    unsigned int useless;
    short nbentry;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &useless, 4);
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
    wave->useless = useless;
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
    printf("useless: 0x%08X\n", wave->useless);
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
}