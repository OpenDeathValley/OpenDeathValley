#include "odv_resource_text.h"

void *odv_resource_parse_text(struct ODVResourceFile *rfile)
{
    struct ODVResourceText *text = NULL;
    struct ODVResourceTextEntry *entry = NULL;
    unsigned int useless;
    short nbentry;
    size_t numberofbytesread = 0;
    int i;

    numberofbytesread = odv_file_read(rfile->file, &useless, 4);
    if (numberofbytesread != 4) {
        fprintf(stderr, "[-] odv_resource_parse_text - file read 4 failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, &nbentry, 2);
    if (numberofbytesread != 2 || nbentry < 0) {
        fprintf(stderr, "[-] odv_resource_parse_text - file read 2 failed\n");
        return NULL;
    }
    text = calloc(1, sizeof (struct ODVResourceText));
    if (text == NULL) {
        fprintf(stderr, "[-] odv_resource_parse_text - calloc failed\n");
        return NULL;
    }
    text->useless = useless;
    text->nbentry = nbentry;
    text->entries = calloc(nbentry, sizeof (struct ODVResourceTextEntry*));
    for (i = 0; i < text->nbentry; i++) {
        entry = odv_ressource_parse_text_entry(rfile);
        if (entry == NULL) {
            odv_resource_clean_text(text);
            return NULL;
        }
        text->entries[i] = entry;
    }
    return text;
}

struct ODVResourceTextEntry *odv_ressource_parse_text_entry(struct ODVResourceFile *rfile)
{
    struct ODVResourceTextEntry *entry = NULL;
    size_t numberofbytesread = 0;
    unsigned short length;
    wchar_t *wbuf = NULL;

    numberofbytesread = odv_file_read(rfile->file, &length, 2);
    if (numberofbytesread != 2) {
        fprintf(stderr, "[-] odv_ressource_parse_text_entry - file read 2 failed\n");
        return NULL;
    }
    wbuf = calloc(length + 1, sizeof (wchar_t));
    if (wbuf == NULL) {
        fprintf(stderr, "[-] odv_ressource_parse_text_entry - calloc failed\n");
        return NULL;
    }
    numberofbytesread = odv_file_read(rfile->file, wbuf, (length * 2));
    if (numberofbytesread != (size_t)(length * 2)) {
        fprintf(stderr, "[-] odv_ressource_parse_text_entry - file read %d failed\n", length);
        free(wbuf);
        return NULL;
    }
    entry = calloc(1, sizeof (struct ODVResourceTextEntry));
    if (entry == NULL) {
        fprintf(stderr, "[-] odv_ressource_parse_text_entry - calloc failed\n");
        free(wbuf);
        return NULL;
    }
    entry->length = length;
    entry->wbuf = wbuf;
    return entry;
}

void odv_resource_text_info(const struct ODVResourceText *text)
{
    int i;

    if (text == NULL)
        return;
    printf("[- ODV RESOURCE TEXT information -]\n");
    printf("useless: 0x%08X\n", text->useless);
    printf("nbentry: 0x%04X (%d)\n", text->nbentry, text->nbentry);
    if (text->entries != NULL) {
        for (i = 0; i < text->nbentry; i++) {
            if (text->entries[i] != NULL) {
                printf("(%d): %ls\n", i, text->entries[i]->wbuf);
                /* wprintf(L"(%d): %s\n", i, text->entries[i]->wbuf); */
            }
        }
    }

    printf("[---------------------------------]\n");
}

void odv_resource_clean_text_entry(struct ODVResourceTextEntry *entry)
{
    if (entry == NULL)
        return;
    entry->length = 0;
    if (entry->wbuf != NULL)
        free(entry->wbuf);
    entry->wbuf = NULL;
    free(entry);
}

void odv_resource_clean_text(struct ODVResourceText *text)
{
    int i;

    if (text == NULL)
        return;
    if (text->entries != NULL) {
        for (i = 0; i < text->nbentry; i++) {
            if (text->entries[i] != NULL) {
                odv_resource_clean_text_entry(text->entries[i]);
                text->entries[i] = NULL;
            }
        }
        free(text->entries);
    }
    free(text);
}