#include "odv_utils.h"

void hex_dump(void *data, int size)
{
    unsigned char *p = (unsigned char*)data;
    unsigned char c;
    int n;
    char bytestr[4] = {0};
    char addrstr[10] = {0};
    char hexstr[16 * 3 + 5] = {0};
    char charstr[16 * 1 + 5] = {0};

    for (n = 1; n <= size; n++) {
        if (n % 16 == 1) {
            snprintf(addrstr, sizeof(addrstr), "%.4x", (unsigned int)((unsigned char*)p - (unsigned char*)data));
        }
        c = *p;
        if (isprint(c) == 0) {
            c = '.';
        }
        snprintf(bytestr, sizeof(bytestr), "%02X ", *p);
        strncat(hexstr, bytestr, sizeof(hexstr) - strlen(hexstr) - 1);
        snprintf(bytestr, sizeof(bytestr), "%c", c);
        strncat(charstr, bytestr, sizeof(charstr) - strlen(charstr) - 1);
        if (n % 16 == 0) {
            printf("[%4.4s]   %-50.50s  %s\n", addrstr, hexstr, charstr);
            hexstr[0] = 0;
            charstr[0] = 0;
        }
        else if (n % 8 == 0) {
            strncat(hexstr, "  ", sizeof(hexstr)-strlen(hexstr)-1);
            strncat(charstr, " ", sizeof(charstr)-strlen(charstr)-1);
        }
        p++;
    }
    if (strlen(hexstr) > 0) {
        printf("[%4.4s]   %-50.50s  %s\n", addrstr, hexstr, charstr);
    }
}

int arg_longf(const char *argv, const char *arg_name, size_t *pos_argv) 
{
    if (!strncmp(&argv[*pos_argv + 1], arg_name, strlen(arg_name))) {
        *pos_argv += strlen(arg_name);
        return 1;
    }
    return 0;
}

int file_exists(const char *filename)
{
    struct stat path_stat;

    return (stat(filename, &path_stat) != 0);
}

int is_regular_file(const char *filename)
{
    struct stat path_stat;

    stat(filename, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int is_folder_writable(const char* filename) {
    return (access(filename, W_OK) != 0);
}

int get_basename(char *path, char *filename, size_t filename_length)
{
    #ifdef WINDOWS
        char fname[256];    // _MAX_FNAME
        char ext[256];      // _MAX_EXT
        _splitpath_s(path, NULL, 0x00, NULL, 0x00, fname, sizeof (fname), ext, sizeof (ext));
        snprintf(filename, filename_length, "%s%s", fname, ext);
    #else
        char *fname_ext = basename(path);
        snprintf(filename, filename_length, "%s", fname_ext);
    #endif

    return 0;
}

void unicode_to_utf8(wchar_t c, char *buf)
{
    // 7 bit Unicode encoded as plain ascii
    if (c < (1 << 7)) {
        *buf++ = (unsigned char)(c);
    }
    // 11 bit Unicode encoded in 2 UTF-8 bytes
    else if (c < (1 << 11)) {
        *buf++ = (unsigned char)((c >> 6) | 0xC0);
        *buf++ = (unsigned char)((c & 0x3F) | 0x80);
    }
    // 16 bit Unicode encoded in 3 UTF-8 bytes
    else if (c < (1 << 16)) {
        *buf++ = (unsigned char)(((c >> 12)) | 0xE0);
        *buf++ = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
        *buf++ = (unsigned char)((c & 0x3F) | 0x80);
    }
    // 21 bit Unicode encoded in 4 UTF-8 bytes
    //else if (c < (1 << 21)) {
    //    *buf++ = (unsigned char)(((c >> 18)) | 0xF0);
    //    *buf++ = (unsigned char)(((c >> 12) & 0x3F) | 0x80);
    //    *buf++ = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
    //    *buf++ = (unsigned char)((c & 0x3F) | 0x80);
    //}
    *buf = 0x00;
}