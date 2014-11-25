#include "odv_resource_cur.h"

void *odv_resource_parse_cur(struct ODVResourceFile *rfile)
{
    struct ODVResourceCur *cur = NULL;
    struct ODVImage *entry = NULL;
    unsigned int unk_dword_00;
    unsigned short unk_word_00;
    unsigned short unk_word_01;
    unsigned short unk_word_02;
    unsigned short unk_word_03;
    int nbentry = 0;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &unk_dword_00, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_cur - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &unk_word_00, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_resource_parse_cur - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &unk_word_01, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_resource_parse_cur - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &unk_word_02, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_resource_parse_cur - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &unk_word_03, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_resource_parse_cur - file read 2 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &nbentry, 4);
    if (numberofbytesread != 4 || nbentry < 0) {
        fprintf(stderr, "[-] odv_resource_parse_cur - file read 4 failed\n");
        return NULL;
    }
    cur = calloc(1, sizeof (struct ODVResourceCur));
    if (cur == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_cur - calloc failed\n");
        return NULL;
    }
    cur->unk_dword_00 = unk_dword_00;
    cur->unk_word_00 = unk_word_00;
    cur->unk_word_01 = unk_word_01;
    cur->unk_word_02 = unk_word_02;
    cur->unk_word_03 = unk_word_03;
    cur->nbentry = nbentry;
    cur->entries = calloc(nbentry, sizeof (struct ODVImage*));
    if (cur->entries == NULL) {
        free(cur);
        fprintf(stderr, "[-] odv_resource_parse_cur - calloc failed\n");
        return NULL;
    }
    for (i = 0; i < cur->nbentry; i++) {
        entry = odv_image_parse(rfile->file);
        if (entry == NULL) {
            odv_resource_clean_cur(cur);
            return NULL;
        }
        cur->entries[i] = entry;
    }
    return cur;
}

void odv_resource_cur_info(const struct ODVResourceCur *cur)
{
    int i;

    if (cur == NULL)
        return;
    printf("[- ODV RESOURCE CUR information -]\n");
    printf("unk_dword_00: 0x%08X\n", cur->unk_dword_00);
    printf("unk_word_00: 0x%04X\n", cur->unk_word_00);
    printf("unk_word_01: 0x%04X\n", cur->unk_word_01);
    printf("unk_word_02: 0x%04X\n", cur->unk_word_02);
    printf("unk_word_03: 0x%04X\n", cur->unk_word_03);
    printf("nbentry: 0x%04X (%d)\n", cur->nbentry, cur->nbentry);
    if (cur->entries) {
        for (i = 0; i < cur->nbentry; i++) {
            if (cur->entries[i] != NULL) {
                odv_image_info(cur->entries[i]);
            }
        }
    }
    printf("[---------------------------------]\n");
}

void odv_resource_clean_cur(struct ODVResourceCur *cur)
{
    int i;

    if (cur == NULL)
        return;
    if (cur->entries != NULL) {
        for (i = 0; i < cur->nbentry; i++) {
            if (cur->entries[i] != NULL) {
                odv_image_clean(cur->entries[i]);
                cur->entries[i] = NULL;
            }
        }
        free(cur->entries);
    }
    free(cur);
}