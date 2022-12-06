#include "odv_fnt_handler.h"

struct ODVFnt *odv_fnt_open(const char *filename)
{
    struct ODVFile *file = NULL;
    struct ODVFnt *fnt = NULL;
    struct ODVFntChar *entry = NULL;
    unsigned int i;

    file = odv_file_open(filename);
    if (file == NULL) {
        fprintf(stderr, "[-] odv_fnt_open - odv_file_open failed\n");
        return NULL;
    }
    fnt = calloc(1, sizeof (struct ODVFnt));
    if (fnt == NULL) {
        fprintf(stderr, "[-] odv_fnt_open - calloc failed\n");
        odv_file_close(file);
        return NULL;
    }
    fnt->file = file;
    if (odv_fnt_parse_header(fnt) == 0) {
        odv_fnt_close(fnt);
        return NULL;
    }
    fnt->char_entries = calloc(fnt->header.nb_entry, sizeof(struct ODVFntChar*));
    if (fnt->char_entries == NULL) {
        fprintf(stderr, "[-] odv_fnt_open - calloc failed\n");
        odv_fnt_close(fnt);
        return NULL;
    }
    for (i = 0; i < fnt->header.nb_entry; i++) {
        entry = odv_fnt_parse_entry(fnt);
        if (entry == NULL) {
            odv_fnt_close(fnt);
            return NULL;
        }
        fnt->char_entries[i] = entry;
    }
    /* Contains two image : image_00, image_01 */
    fnt->imgmap = odv_imagemap_parse_nb(fnt->file, 2);
    if (fnt->imgmap == NULL) {
        odv_fnt_close(fnt);
        return NULL;
    }
    return fnt;
}

struct ODVFntChar *odv_fnt_parse_entry(struct ODVFnt *fnt)
{
    struct ODVFntChar *entry = NULL;
    size_t numberofbytesread = 0;

    entry = calloc(1, sizeof (struct ODVFntChar));
    if (entry == NULL) {
        fprintf(stderr, "[-] odv_fnt_parse_entry - calloc failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(fnt->file, entry, sizeof (struct ODVFntChar));
    if (numberofbytesread != sizeof (struct ODVFntChar)) {
        fprintf(stderr, "[-] odv_fnt_parse_header - file read %zu failed\n", sizeof (struct ODVFntChar));
        free(entry);
        return NULL;
    }
    return entry;
}

int odv_fnt_parse_header(struct ODVFnt *fnt)
{
    size_t numberofbytesread = 0;

    numberofbytesread = odv_file_read(fnt->file, &fnt->header, sizeof (struct ODVFntHeader));
    if (numberofbytesread != sizeof (struct ODVFntHeader)) {
        fprintf(stderr, "[-] odv_fnt_parse_header - file read %zu failed\n", sizeof (struct ODVFntHeader));
        return 0;
    }
    if (strncmp(fnt->header.signature, FNT_SIGNATURE, 6) != 0) {
        fprintf(stderr, "[-] odv_fnt_parse_header - wrong singature\n");
        return 0;
    }
    if (fnt->header.version >= 0x200) {
        numberofbytesread = odv_file_read(fnt->file, &fnt->unk_dword_00, 4);
        if (numberofbytesread != 4) {
            fprintf(stderr, "[-] odv_fnt_parse_header - file read 4 failed\n");
            return 0;
        }
    }
    return 1;
}

void odv_fnt_info(const struct ODVFnt *fnt)
{
    if (fnt == NULL)
        return;
    printf("[- ODV FNT information -]\n");
    printf("version         = 0x%08X\n", fnt->header.version);
    printf("font name       = %s\n", fnt->header.font_name);
    printf("type            = 0x%04X\n", fnt->header.type);
    printf("unk_word_00     = 0x%04X\n", fnt->header.unk_word_00);
    printf("unk_dword_01    = 0x%08X\n", fnt->header.unk_dword_01);
    printf("unk_dword_02    = 0x%08X\n", fnt->header.unk_dword_02);
    printf("unk_dword_03    = 0x%08X\n", fnt->header.unk_dword_03);
    printf("nb_entry        = 0x%08X\n", fnt->header.nb_entry);
    if (fnt->header.version >= 0x200) {
        printf("unk_dword_00    = 0x%08X\n", fnt->unk_dword_00);
    }
    if (fnt->imgmap != NULL) {
        odv_imagemap_info(fnt->imgmap);
    }
    printf("[---------------------------------]\n");
}

void odv_fnt_close(struct ODVFnt *fnt)
{
    unsigned int i;

    if (fnt == NULL)
        return;
    if (fnt->file != NULL)
        odv_file_close(fnt->file);
    if (fnt->char_entries != NULL) {
        for (i = 0; i < fnt->header.nb_entry; i++) {
            if (fnt->char_entries[i] != NULL) {
                free(fnt->char_entries[i]);
                fnt->char_entries[i] = NULL;
            }
        }
        free(fnt->char_entries);
    }
    if (fnt->imgmap != NULL)
        odv_imagemap_clean(fnt->imgmap);
    free(fnt);
}