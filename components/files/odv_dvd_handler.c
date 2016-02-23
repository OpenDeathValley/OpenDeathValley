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
        fprintf(stderr, "[-] odv_dvd_open - calloc failed\n");
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

int odv_dvd_add_entry(struct ODVDDvdFile *dfile, void *entry, unsigned int signature)
{
    struct ODVDDvdEntry *dvdentry = NULL;

    dfile->entries = realloc(dfile->entries, sizeof (struct ODVDDvdEntry *) * (dfile->nbentry + 1));
    if (dfile->entries == NULL) {
        fprintf(stderr, "[-] odv_dvd_add_entry - realloc failed\n");
        return 0;
    }
    dvdentry = calloc(1, sizeof (struct ODVDDvdEntry));
    if (dvdentry == NULL) {
        fprintf(stderr, "[-] odv_dvd_add_entry - calloc failed\n");
        return 0;
    }
    dvdentry->signature = signature;
    dvdentry->data = entry;
    dfile->entries[dfile->nbentry] = dvdentry;
    dfile->nbentry = dfile->nbentry + 1;
    return 1;
}

int odv_dvd_parse_entry(struct ODVDDvdFile *dfile)
{
    unsigned int signature;
    unsigned int length;
    size_t numberofbytesread = 0;
    unsigned int saved_pos = 0;
    void *entry = NULL;

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
    switch (signature) {
        case MISC_SIGNATURE:
            if ((entry = odv_dvd_parse_misc(dfile)) == NULL)
                return 0;
            if (odv_dvd_add_entry(dfile, entry, MISC_SIGNATURE) == 0) {
                free(entry);
                return 0;
            }
        break;

        case BGND_SIGNATURE:
            if ((entry = odv_dvd_parse_bgnd(dfile)) == NULL)
                return 0;
            if (odv_dvd_add_entry(dfile, entry, BGND_SIGNATURE) == 0) {
                free(entry);
                return 0;
            }
        break;

        case SCRP_SIGNATURE:
            if ((entry = odv_dvd_parse_scrp(dfile)) == NULL)
                return 0;
            if (odv_dvd_add_entry(dfile, entry, SCRP_SIGNATURE) == 0) {
                free(entry);
                return 0;
            }
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
    unsigned int i;

    if (dfile == NULL)
        return;
    if (dfile->entries != NULL) {
        for (i = 0; i < dfile->nbentry; i++) {
            if (dfile->entries[i] != NULL) {
                switch (dfile->entries[i]->signature) {
                    case MISC_SIGNATURE:
                        odv_dvd_misc_info(dfile->entries[i]->data);
                    break;

                    case BGND_SIGNATURE:
                        odv_dvd_bgnd_info(dfile->entries[i]->data);
                    break;

                    case SCRP_SIGNATURE:
                        odv_dvd_scrp_info(dfile->entries[i]->data);
                    break;

                    default:
                        fprintf(stderr, "[-] odv_dvd_info - unknow signature %08X\n", dfile->entries[i]->signature);
                }
            }
        }
    }
}

void *odv_dvd_parse_misc(struct ODVDDvdFile *dfile)
{
    unsigned int version;
    size_t numberofbytesread = 0;
    struct ODVDvdMisc *misc = NULL;

    if (dfile == NULL)
        return NULL;
    numberofbytesread = odv_file_read(dfile->file, &version, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_dvd_parse_misc - file read 4 failed\n");
        return NULL;
    }
    if (version != 6) {
        fprintf(stderr, "[-] odv_dvd_parse_misc - version not valid\n");
        return NULL;
    }
    misc = calloc(1, sizeof (struct ODVDvdMisc));
    if (misc == NULL) {
        fprintf(stderr, "[-] odv_dvd_parse_misc - calloc failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(dfile->file, misc, sizeof (struct ODVDvdMisc) - (sizeof (unsigned short) * 2));
    if (numberofbytesread != (sizeof (struct ODVDvdMisc) - (sizeof (unsigned short) * 2))) {
        fprintf(stderr, "[-] odv_dvd_parse_misc - file read %lu failed\n", sizeof (struct ODVDvdMisc) - (sizeof (unsigned short) * 2));
        free(misc);
        return NULL;
    }
    if (misc->unk_byte_04 == 1) {
        numberofbytesread = odv_file_read(dfile->file, &misc->unk_word_04, sizeof (unsigned short) * 2);
        if (numberofbytesread != (sizeof (unsigned short) * 2)) {
            fprintf(stderr, "[-] odv_dvd_parse_misc - file read %lu failed\n", sizeof (unsigned short) * 2);
            free(misc);
            return NULL;
        }
    }
    return misc;
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

void odv_dvd_clean_misc(struct ODVDvdMisc *misc)
{
    if (misc == NULL)
        return;
    free(misc);
}

void *odv_dvd_parse_bgnd(struct ODVDDvdFile *dfile)
{
    unsigned int version;
    unsigned short filename_length = 0;
    unsigned char *filename = NULL;
    size_t numberofbytesread = 0;
    struct ODVDvdBgnd *bgnd = NULL;

    if (dfile == NULL)
        return NULL;
    numberofbytesread = odv_file_read(dfile->file, &version, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_dvd_parse_bgnd - file read 4 failed\n");
        return NULL;
    }
    if (version != 4) {
        fprintf(stderr, "[-] odv_dvd_parse_bgnd - version not valid\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(dfile->file, &filename_length, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_dvd_parse_bgnd - file read 2 failed\n");
        return NULL;
    }
    filename = calloc(1, filename_length + 1);
    if (filename == NULL) {
        fprintf(stderr, "[-] odv_dvd_parse_bgnd - calloc failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(dfile->file, filename, filename_length);
    if (numberofbytesread != filename_length) {
        fprintf(stderr, "[-] odv_dvd_parse_bgnd - file read %d failed\n", filename_length);
        free(filename);
        return NULL;
    }
    bgnd = calloc(1, sizeof (struct ODVDvdBgnd));
    if (bgnd == NULL) {
        fprintf(stderr, "[-] odv_dvd_parse_bgnd - calloc failed\n");
        free(filename);
        return NULL;
    }
    bgnd->filename = filename; /* .dvm */
    bgnd->img = odv_image_parse(dfile->file);
    if (bgnd->img == NULL) {
        free(filename);
        free(bgnd);
        return NULL;
    }
    return bgnd;
}

void odv_dvd_bgnd_info(const struct ODVDvdBgnd *bgnd)
{
    if (bgnd == NULL)
        return;
    printf("[- ODV DVD BGND information -]\n");
    printf("filename (.dvm) : %s\n", bgnd->filename);
    odv_image_info(bgnd->img);
    printf("[----------------------------]\n");
}

void odv_dvd_clean_bgnd(struct ODVDvdBgnd *bgnd)
{
    if (bgnd == NULL)
        return;
    if (bgnd->filename != NULL)
        free(bgnd->filename);
    if (bgnd->img != NULL)
        odv_image_clean(bgnd->img);
    free(bgnd);
}

void *odv_dvd_parse_scrp_entry(struct ODVDDvdFile *dfile)
{
    unsigned short type_entry;
    size_t numberofbytesread = 0;
    unsigned short coord_y;
    unsigned short coord_x;
    unsigned short unk_word_00;
    unsigned short unk_word_01;
    unsigned short unk_word_02;
    unsigned char unk_byte_00;
    unsigned char classname_present;

    numberofbytesread = odv_file_read(dfile->file, &type_entry, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_dvd_parse_scrp_entry - file read 2 failed\n");
        return NULL;
    }
    /* printf("[+] type_entry = 0x%04X\n", type_entry); */
    if (type_entry == 1) {
        numberofbytesread = odv_file_read(dfile->file, &coord_y, 2);
        if (numberofbytesread != 2) {
            fprintf(stderr, "[-] odv_dvd_parse_scrp_entry - file read 2 failed\n");
            return NULL;
        }
        numberofbytesread = odv_file_read(dfile->file, &coord_x, 2);
        if (numberofbytesread != 2) {
            fprintf(stderr, "[-] odv_dvd_parse_scrp_entry - file read 2 failed\n");
            return NULL;
        }
        numberofbytesread = odv_file_read(dfile->file, &unk_word_00, 2);
        if (numberofbytesread != 2) {
            fprintf(stderr, "[-] odv_dvd_parse_scrp_entry - file read 2 failed\n");
            return NULL;
        }
        numberofbytesread = odv_file_read(dfile->file, &unk_word_01, 2);
        if (numberofbytesread != 2) {
            fprintf(stderr, "[-] odv_dvd_parse_scrp_entry - file read 2 failed\n");
            return NULL;
        }
        numberofbytesread = odv_file_read(dfile->file, &unk_byte_00, 1);
        if (numberofbytesread != 1) {
            fprintf(stderr, "[-] odv_dvd_parse_scrp_entry - file read 1 failed\n");
            return NULL;
        }
        /* printf("unk_word_00: 0x%04X\n", unk_word_00);
        printf("unk_word_01: 0x%04X\n", unk_word_01);
        printf("unk_word_02: 0x%04X\n", unk_word_02);
        printf("unk_word_03: 0x%04X\n", unk_word_03);
        printf("unk_byte_00: 0x%02X\n", unk_byte_00); */

        printf("(0x%04X, 0x%04X),\n", coord_y, coord_x);

    }
    else if (type_entry != 2) {
        dfile->file->pos += (4 * type_entry);
        numberofbytesread = odv_file_read(dfile->file, &unk_word_00, 2);
        if (numberofbytesread != 2) {
            fprintf(stderr, "[-] odv_dvd_parse_scrp_entry - file read 2 failed\n");
            return NULL;
        }
        numberofbytesread = odv_file_read(dfile->file, &unk_word_01, 2);
        if (numberofbytesread != 2) {
            fprintf(stderr, "[-] odv_dvd_parse_scrp_entry - file read 2 failed\n");
            return NULL;
        }
        numberofbytesread = odv_file_read(dfile->file, &classname_present, 1);
        if (numberofbytesread != 1) {
            fprintf(stderr, "[-] odv_dvd_parse_scrp_entry - file read 1 failed\n");
            return NULL;
        }
        if (classname_present == 1) {
            numberofbytesread = odv_file_read(dfile->file, &unk_word_02, 2);
            if (numberofbytesread != 2) {
                fprintf(stderr, "[-] odv_dvd_parse_scrp_entry - file read 2 failed\n");
                return NULL;
            }
            dfile->file->pos += unk_word_02;
        }
    }
    else {
        fprintf(stderr, "odv_dvd_parse_scrp_entry - type_entry not handled\n");
        return NULL;
    }

    return NULL;
}

void *odv_dvd_parse_scrp(struct ODVDDvdFile *dfile)
{
    struct ODVDvdScrp *scrp = NULL;
    unsigned int version;
    size_t numberofbytesread = 0;
    short nbentry;
    int i;

    if (dfile == NULL)
        return NULL;
    numberofbytesread = odv_file_read(dfile->file, &version, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_dvd_parse_scrp - file read 4 failed\n");
        return NULL;
    }
    if (version != 1) {
        fprintf(stderr, "[-] odv_dvd_parse_scrp - version not valid\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(dfile->file, &nbentry, 2);
    if (numberofbytesread != 2 || nbentry < 0) {
        fprintf(stderr, "[-] odv_dvd_parse_scrp - file read 2 failed\n");
        return NULL;
    }
    scrp = calloc(1, sizeof (struct ODVDvdScrp));
    if (scrp == NULL) {
        fprintf(stderr, "[-] odv_dvd_parse_scrp - calloc failed\n");
        return NULL;
    }
    scrp->nbentry = nbentry;
    for (i = 0; i < scrp->nbentry; i++) {
        odv_dvd_parse_scrp_entry(dfile);
    }
    return scrp;
}

void odv_dvd_scrp_info(const struct ODVDvdScrp *scrp)
{
    if (scrp == NULL)
        return;
    printf("[- ODV DVD SCRP information -]\n");
    printf("nbentry : %08X\n", scrp->nbentry);
    printf("[----------------------------]\n");
}

void odv_dvd_clean_scrp(struct ODVDvdScrp *scrp)
{
    if (scrp == NULL)
        return;
    free(scrp);
}

void odv_dvd_close(struct ODVDDvdFile *dfile)
{
    unsigned int i;

    if (dfile == NULL)
        return;
    if (dfile->file != NULL)
        odv_file_close(dfile->file);
    if (dfile->entries != NULL) {
        for (i = 0; i < dfile->nbentry; i++) {
            if (dfile->entries[i] != NULL) {
                switch (dfile->entries[i]->signature) {
                    case MISC_SIGNATURE:
                        odv_dvd_clean_misc(dfile->entries[i]->data);
                        free(dfile->entries[i]);
                        dfile->entries[i] = NULL;
                    break;

                    case BGND_SIGNATURE:
                        odv_dvd_clean_bgnd(dfile->entries[i]->data);
                        free(dfile->entries[i]);
                        dfile->entries[i] = NULL;
                    break;

                    case SCRP_SIGNATURE:
                        odv_dvd_clean_scrp(dfile->entries[i]->data);
                        free(dfile->entries[i]);
                        dfile->entries[i] = NULL;
                    break;

                    default:
                        fprintf(stderr, "[-] odv_dvd_close - unknow signature %08X\n", dfile->entries[i]->signature);
                }
            }
        }
        free(dfile->entries);
    }
    free(dfile);
}