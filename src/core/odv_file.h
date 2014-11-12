#ifndef OPENDV_FILE_H
#define OPENDV_FILE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef WINDOWS
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/mman.h>
#endif

struct ODVFile
{
    char filename[FILENAME_MAX];
    char *buf;
    unsigned int length;
    unsigned int pos;

#ifdef WINDOWS
    HANDLE file;
    HANDLE map;
#else
    int fd;
#endif
};

struct ODVFile *odv_file_open(const char *filename);
void odv_file_info(const struct ODVFile *file);

int odv_file_read(struct ODVFile *file, void *buf, size_t count);
int odv_file_readline(struct ODVFile *file, char *buf, size_t count);
void odv_file_seek(struct ODVFile *file, unsigned int offset);
int odv_file_close(struct ODVFile *file);

struct ODVFile *odv_file_open_win(char *filename);
int odv_file_close_win(struct ODVFile *file);

#endif /* OPENDV_FILE_H */
