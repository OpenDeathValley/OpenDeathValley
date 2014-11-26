#include "odv_dvd_handler.h"

struct ODVDDvdFile *odv_dvd_open(const char *filename)
{
    struct ODVFile *file = NULL;
    struct ODVDDvdFile *dfile = NULL;

    file = odv_file_open(filename);
    if (file == NULL) {
        fprintf(stderr, "[-] odv_dvd_open - odv_file_open failed\n");
        return NULL;
    }
    dfile = calloc(1, sizeof (struct ODVDDvdFile));
    if (dfile == NULL) {
        fprintf(stderr, "[-] odv_dvd_open - malloc failed\n");
        odv_file_close(file);
        return NULL;
    }
    dfile->file = file;
    if (odv_dvd_parse(dfile) == 0) {
        odv_dvd_close(dfile);
        return NULL;
    }
    return dfile;
}

int odv_dvd_parse(struct ODVDDvdFile *dfile)
{
    if (dfile == NULL)
        return 0;
    while (dfile->file->pos < dfile->file->length) {
        if (odv_dvd_parse_entry(dfile) == 0) {
            return 0;
        }
    }
    return 1;
}

int odv_dvd_parse_entry(struct ODVDDvdFile *dfile)
{
    unsigned int signature;
    unsigned int length;
    size_t numberofbytesread = 0;
    unsigned int saved_pos = 0;

    if (dfile == NULL)
        return 0;
    numberofbytesread = odv_file_read(dfile->file, &signature, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_dvd_parse_entry - file read 4 failed\n");
        return 0;
    }
    numberofbytesread = odv_file_read(dfile->file, &length, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_dvd_parse_entry - file read 4 failed\n");
        return 0;
    }
    saved_pos = dfile->file->pos;
    /* printf("[+] signature: 0x%08X\n", signature); */
    switch (signature) {
        case MISC_SIGNATURE:
            if (odv_dvd_parse_misc(dfile) == 0)
                return 0;
        break;

        case BGND_SIGNATURE:
            if (odv_dvd_parse_bgnd(dfile) == 0)
                return 0;
        break;

        default:
            printf("[-] signature 0x%08X not handled\n", signature);
            dfile->file->pos = saved_pos + length;
    }
    /* dfile->file->pos = saved_pos + length; */
    return 1;
}

void odv_dvd_info(struct ODVDDvdFile *dfile)
{
    if (dfile == NULL)
        return;
}

int odv_dvd_parse_misc(struct ODVDDvdFile *dfile)
{
    unsigned int version;
    size_t numberofbytesread = 0;
    struct ODVDvdMisc *misc = NULL;

    if (dfile == NULL)
        return 0;
    numberofbytesread = odv_file_read(dfile->file, &version, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_dvd_parse_misc - file read 4 failed\n");
        return 0;
    }
    if (version != 6) {
        fprintf(stderr, "[-] odv_dvd_parse_misc - version not valid\n");
        return 0;
    }
    misc = calloc(1, sizeof (struct ODVDvdMisc));
    if (misc == NULL) {
        fprintf(stderr, "[-] odv_dvd_parse_misc - calloc failed\n");
        return 0;
    }
    numberofbytesread = odv_file_read(dfile->file, misc, sizeof (struct ODVDvdMisc) - (sizeof (unsigned short) * 2));
    if (numberofbytesread != (sizeof (struct ODVDvdMisc) - (sizeof (unsigned short) * 2))) {
        fprintf(stderr, "[-] odv_dvd_parse_misc - file read %d failed\n", sizeof (struct ODVDvdMisc) - (sizeof (unsigned short) * 2));
        free(misc);
        return 0;
    }
    if (misc->unk_byte_04 == 1) {
        numberofbytesread = odv_file_read(dfile->file, &misc->unk_word_04, sizeof (unsigned short) * 2);
        if (numberofbytesread != (sizeof (unsigned short) * 2)) {
            fprintf(stderr, "[-] odv_dvd_parse_misc - file read %d failed\n", sizeof (unsigned short) * 2);
            free(misc);
            return 0;
        }
    }
    return 1;
}

void odv_dvd_misc_info(const struct ODVDvdMisc *misc)
{
    if (misc == NULL)
        return;
    printf("[- ODV DVD MISC information -]\n");
    printf("unk_byte_00 : 0x%02X\n", misc->unk_byte_00);
    printf("unk_word_00 : 0x%04X\n", misc->unk_word_00);
    printf("unk_word_01 : 0x%04X\n", misc->unk_word_01);
    printf("unk_dword_00: 0x%08X\n", misc->unk_dword_00);
    printf("unk_dword_01: 0x%08X\n", misc->unk_dword_01);
    printf("unk_dword_02: 0x%08X\n", misc->unk_dword_02);
    printf("unk_byte_01 : 0x%02X\n", misc->unk_byte_01);
    printf("unk_word_02 : 0x%04X\n", misc->unk_word_02);
    printf("unk_dword_03: 0x%08X\n", misc->unk_dword_03);
    printf("unk_byte_02 : 0x%02X\n", misc->unk_byte_02);
    printf("unk_byte_03 : 0x%02X\n", misc->unk_byte_03);
    printf("unk_dword_04: 0x%08X\n", misc->unk_dword_04);
    printf("unk_byte_04 : 0x%02X\n", misc->unk_byte_04);
    if (misc->unk_byte_04 == 1) {
        printf("unk_word_04 : 0x%04X\n", misc->unk_word_04);
        printf("unk_word_05 : 0x%04X\n", misc->unk_word_05);
    }
    printf("[----------------------------]\n");
}

void odv_dvd_misc_clean(struct ODVDvdMisc *misc)
{
    if (misc == NULL)
        return;
    free(misc);
}

int odv_dvd_parse_bgnd(struct ODVDDvdFile *dfile)
{
    unsigned int version;
    unsigned short filename_length = 0;
    unsigned char *filename = NULL;
    size_t numberofbytesread = 0;
    struct ODVDvdBgnd *bgnd = NULL;

    if (dfile == NULL)
        return 0;
    numberofbytesread = odv_file_read(dfile->file, &version, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_dvd_parse_bgnd - file read 4 failed\n");
        return 0;
    }
    if (version != 4) {
        fprintf(stderr, "[-] odv_dvd_parse_bgnd - version not valid\n");
        return 0;
    }
    numberofbytesread = odv_file_read(dfile->file, &filename_length, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_dvd_parse_bgnd - file read 2 failed\n");
        return 0;
    }
    filename = calloc(1, filename_length + 1);
    if (filename == NULL) {
        fprintf(stderr, "[-] odv_dvd_parse_bgnd - calloc failed\n");
        return 0;
    }
    numberofbytesread = odv_file_read(dfile->file, filename, filename_length);
    if (numberofbytesread != filename_length) {
        fprintf(stderr, "[-] odv_dvd_parse_bgnd - file read %d failed\n", filename_length);
        free(filename);
        return 0;
    }
    bgnd = calloc(1, sizeof (struct ODVDvdBgnd));
    if (bgnd == NULL) {
        fprintf(stderr, "[-] odv_dvd_parse_bgnd - calloc failed\n");
        free(filename);
        return 0;
    }
    bgnd->filename = filename; /* .dvm */
    bgnd->img = odv_image_parse(dfile->file);
    if (bgnd->img == NULL) {
        free(filename);
        free(bgnd);
        return 0;
    }
    return 1;
}

void odv_dvd_bgnd_info(const struct ODVDvdBgnd *bgnd)
{
    if (bgnd == NULL)
        return;
    printf("[- ODV DVD BGND information -]\n");
    printf("filename : %s\n", bgnd->filename);
    odv_image_info(bgnd->img);
    printf("[----------------------------]\n");
}

void odv_dvd_bgnd_clean(struct ODVDvdBgnd *bgnd)
{
    if (bgnd == NULL)
        return;
    if (bgnd->filename != NULL)
        free(bgnd->filename);
    if (bgnd->img != NULL)
        odv_image_clean(bgnd->img);
    free(bgnd);
}

void odv_dvd_close(struct ODVDDvdFile *dfile)
{
    if (dfile == NULL)
        return;
    if (dfile->file != NULL)
        odv_file_close(dfile->file);
    free(dfile);
}