#include "odv_fxg_handler.h"

struct ODVSoundFXGFile *odv_fxg_open(const char *filename)
{
    struct ODVFile *file = NULL;
    struct ODVSoundFXGFile *sfile = NULL;
    struct ODVSoundFXGEntry *entry = NULL;
    int i;

    file = odv_file_open(filename);
    if (file == NULL) {
        fprintf(stderr, "[-] odv_fxg_open - odv_file_open failed\n");
        return NULL;
    }
    sfile = calloc(1, sizeof (struct ODVSoundFXGFile));
    if (sfile == NULL) {
        fprintf(stderr, "[-] odv_fxg_open - calloc failed\n");
        odv_file_close(file);
        return NULL;
    }
    sfile->file = file;
    if (odv_fxg_parse_header(sfile) == 0) {
        odv_fxg_close(sfile);
        return NULL;
    }
    sfile->entries = calloc(sfile->nbentry, sizeof(struct ODVSoundFXGEntry*));
    if (sfile->entries == NULL) {
        fprintf(stderr, "[-] odv_fxg_open - calloc failed\n");
        odv_fxg_close(sfile);
        return NULL;
    }
    for (i = 0; i < sfile->nbentry; i++) {
        entry = odv_fxg_parse_entry(sfile);
        if (entry == NULL) {
            odv_fxg_close(sfile);
            return NULL;
        }
        sfile->entries[i] = entry;
    }
    return sfile;
}

int odv_fxg_parse_header(struct ODVSoundFXGFile *sfile)
{
    size_t numberofbytesread = 0;

    numberofbytesread = odv_file_read(sfile->file, &sfile->signature, 4);
    if (numberofbytesread != 4 || sfile->signature != FXG_SIGNATURE) {
        fprintf(stderr, "[-] odv_fxg_parse_header - wrong resource signature\n");
        return 0;
    }
    numberofbytesread = odv_file_read(sfile->file, &sfile->unk_dword_00, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_fxg_parse_header - file read 4 failed\n");
        return 0;
    }
    numberofbytesread = odv_file_read(sfile->file, &sfile->unk_dword_01, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_fxg_parse_header - file read 4 failed\n");
        return 0;
    }
    numberofbytesread = odv_file_read(sfile->file, &sfile->nbentry, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_fxg_parse_header - file read 4 failed\n");
        return 0;
    }
    return 1;
}

struct ODVSoundFXGEntry *odv_fxg_parse_entry(struct ODVSoundFXGFile *sfile)
{
    size_t numberofbytesread = 0;
    unsigned int type_bank = 0;
    unsigned int fx_id = 0;
    unsigned short unk_word_00 = 0;

    numberofbytesread = odv_file_read(sfile->file, &type_bank, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_fxg_parse_header - file read 4 failed\n");
        return 0;
    }
    numberofbytesread = odv_file_read(sfile->file, &fx_id, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_fxg_parse_header - file read 4 failed\n");
        return 0;
    }
    numberofbytesread = odv_file_read(sfile->file, &unk_word_00, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_fxg_parse_header - file read 2 failed\n");
        return 0;
    }
    printf("[+] type_bank   = %08X\n", type_bank);
    printf("[+] type_bank   = %08X\n", fx_id);
    printf("[+] unk_word_00 = %04X\n", unk_word_00);
    return NULL;
}

void odv_fxg_clean_entry(struct ODVSoundFXGEntry *entry)
{
    if (entry == NULL)
        return;
    free(entry);
}

void odv_fxg_close(struct ODVSoundFXGFile *sfile)
{
    int i;

    if (sfile == NULL)
        return;
    if (sfile->file != NULL)
        odv_file_close(sfile->file);
    if (sfile->entries != NULL) {
        for (i = 0; i < sfile->nbentry; i++) {
            if (sfile->entries[i] != NULL) {
                odv_fxg_clean_entry(sfile->entries[i]);
                sfile->entries[i] = NULL;
            }
        }
        free(sfile->entries);
        sfile->entries = NULL;
    }
    free(sfile);
}