#include "odv_file.h"

#ifdef WINDOWS

struct ODVFile *odv_file_open(const char *filename)
{
    struct ODVFile *file = NULL;

    if (filename == NULL)
        return NULL;
    file = malloc(sizeof (struct ODVFile));
    if (file == NULL) {
        fprintf(stderr, "[-] odv_file_open - malloc failed\n");
        return NULL;
    }
    memset(file, 0, sizeof (struct ODVFile));
    strncpy(file->filename, filename, FILENAME_MAX - 1);
    file->file = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (file->file == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "[-] odv_file_open - CreateFileA failed\n");
        free(file);
        return NULL;
    }
    file->length = GetFileSize(file->file, NULL);
    file->map = CreateFileMapping(file->file, NULL, PAGE_READONLY, 0, 0, NULL);
    if (file->map == 0) {
        fprintf(stderr, "[-] odv_file_open - CreateFileMapping failed\n");
        CloseHandle(file->file);
        free(file);
        return NULL;
    }
    file->buf = MapViewOfFile(file->map, FILE_MAP_READ, 0, 0, 0);
    if (file->buf == 0) {
        fprintf(stderr, "[-] odv_file_open - CreateFileMapping failed\n");
        CloseHandle(file->map);
        CloseHandle(file->file);
        free(file);
        return NULL;
    }
    return file;
}

#else

struct ODVFile *odv_file_open(const char *filename)
{
    struct ODVFile *file = NULL;
	struct stat st;

    if (filename == NULL)
        return NULL;
    file = malloc(sizeof (struct ODVFile));
    if (file == NULL) {
        fprintf(stderr, "[-] odv_file_open - malloc failed\n");
        return NULL;
    }
    memset(file, 0, sizeof (struct ODVFile));
    strncpy(file->filename, filename, FILENAME_MAX - 1);
    file->fd = open(filename, O_RDONLY);
    if (file->fd == -1) {
        fprintf(stderr, "[-] odv_file_open - open failed\n");
        free(file);
        return NULL;
    }
    if (fstat(file->fd, &st) == -1) {
        fprintf(stderr, "[-] odv_file_open - fstat failed\n");
        close(file->fd);
        free(file);
        return NULL;
    }
    file->length = st.st_size;
    if ((file->buf = mmap (NULL, file->length, PROT_READ, MAP_PRIVATE, file->fd, 0)) == MAP_FAILED) {
        fprintf(stderr, "[-] odv_file_open - fstat failed\n");
        close(file->fd);
        free(file);
        return NULL;
    }
    return file;
}

#endif

int odv_file_read(struct ODVFile *file, void *buf, size_t count)
{
    size_t length;

    if (buf == NULL)
        return 0;
    if (file->pos > file->length)
        return 0;
    if (count < (file->length - file->pos))
        length = count;
    else
        length = file->length - file->pos;
    if (length > 0) {
        memcpy(buf, file->buf + file->pos, length);
    }
    file->pos += length;
    return length;
}

int odv_file_readline(struct ODVFile *file, char *buf, size_t count)
{
    size_t length;
    char *newline = NULL;

    if (buf == NULL)
        return 0;
    if (file->pos > file->length)
        return 0;
    newline = strchr((const char*)(file->buf + file->pos), 0x0A);
    if (newline == NULL)
        return 0;
    length = (newline + 1) - (file->buf + file->pos);
    if (length > count)
        return 0;
    length = odv_file_read(file, buf, length);
    buf[length] = 0x00;
    return length;
}

void odv_file_seek(struct ODVFile *file, unsigned int offset)
{
    if (offset > file->length)
        return;
    file->pos = offset;
    /* fseek(file->fp, file->pos, SEEK_SET); */
}

int odv_file_close(struct ODVFile *file)
{
    if (file == NULL)
        return 0;
#ifdef WINDOWS
    CloseHandle(file->file);
    CloseHandle(file->map);
    UnmapViewOfFile(file->buf);
#else
    munmap(file->buf, file->length);
    close(file->fd);
#endif
    free(file);
    return 1;
}

/*int odv_file_close_win(struct ODVFile *file)
{
    if (file == NULL)
        return 0;
    CloseHandle(file->file);
    CloseHandle(file->map);
    UnmapViewOfFile(file->buf);
    return 1;
}*/

void odv_file_info(const struct ODVFile *file)
{
    if (file == NULL)
        return;
    printf("[- ODV file information -]\n");
    printf("filename : %s\n", file->filename);
    printf("filesize : 0x%08X\n", file->length);
    printf("position : 0x%08X\n", file->pos);
    printf("[------------------------]\n");
}
