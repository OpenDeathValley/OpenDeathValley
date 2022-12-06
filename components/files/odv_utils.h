#ifndef OPENDV_UTILS_H
#define OPENDV_UTILS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

// Windows does not define the S_ISREG and S_ISDIR macros in stat.h, so we do.
// We have to define _CRT_INTERNAL_NONSTDC_NAMES 1 before #including sys/stat.h
// in order for Microsoft's stat.h to define names like S_IFMT, S_IFREG, and S_IFDIR,
// rather than just defining  _S_IFMT, _S_IFREG, and _S_IFDIR as it normally does.
#define _CRT_INTERNAL_NONSTDC_NAMES 1
#include <sys/stat.h>
#if !defined(S_ISREG) && defined(S_IFMT) && defined(S_IFREG)
  #define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif
#if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
  #define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif

#ifdef WINDOWS
    #include <io.h>
    #define W_OK 02
    #define access _access
    #define snprintf _snprintf
#else
    #include <unistd.h>
    #define MAX_PATH FILENAME_MAX
#endif

#define align4(x) (((((x) - 1) >> 2) << 2) + 4)

#define ARG_LONG(longname)                                              \
    (arg_longf(argv[pos_arg], longname, &pos_argv))                     \

#define ARG_VAL(var, opt)                                               \
    {                                                                   \
        if (argv[pos_arg][pos_argv + 1] == '=') {                       \
            var = &argv[pos_arg][pos_argv + 2];                         \
            pos_argv = length_argv;                                     \
            break;                                                      \
        }                                                               \
        else if ((pos_arg + 1) < argc) {                                \
            var = argv[pos_arg + 1];                                    \
            pos_argv = length_argv;                                     \
            pos_arg = pos_arg + 1;                                      \
        }                                                               \
        else {                                                          \
            fprintf(stderr, "%s: option requires an argument\n", opt);  \
            exit(EXIT_FAILURE);                                         \
        }                                                               \
    }                                                                   \

#define ARG_GETL_BOOL(longname, shortname, var)                         \
    (ARG_LONG(longname)) case shortname: {                              \
        var = 1;                                                        \
        pos_argv = length_argv;                                         \
    }                                                                   \


#define ARG_GETS_BOOL(shortname, var)                                   \
    case shortname: {                                                   \
        var = 1;                                                        \
        break;                                                          \
    }                                                                   \

#define ARG_GETL_VAL(longname, shortname, var)                          \
    (ARG_LONG(longname)) case shortname: {                              \
        ARG_VAL(var, longname)                                          \
    }                                                                   \

void hex_dump(void *data, int size);
int arg_longf(const char *argv, const char *arg_name, size_t *pos_argv);
int file_exists(const char *filename);
int is_regular_file(const char *filename);
int is_folder_writable(const char* filename);

#endif /* OPENDV_UTILS_H */