#include "odv_scb_handler.h"

struct ODVSCBFile *odv_scb_open(const char *filename)
{
    struct ODVFile *file = NULL;
    struct ODVSCBFile *sfile = NULL;
    struct ODVSCBClass *class = NULL;
    int i;

    file = odv_file_open(filename);
    if (file == NULL) {
        fprintf(stderr, "[-] odv_scb_open - odv_file_open failed\n");
        return NULL;
    }
    sfile = calloc(1, sizeof (struct ODVSCBFile));
    if (sfile == NULL) {
        fprintf(stderr, "[-] odv_scb_open - calloc failed\n");
        odv_file_close(file);
        return NULL;
    }
    memset(sfile, 0, sizeof (struct ODVSCBFile));
    sfile->file = file;
    if (odv_scb_parse_header(sfile) == 0) {
        odv_scb_close(sfile);
        return NULL;
    }
    sfile->classes = calloc(sfile->nbclasses, sizeof(struct ODVSCBClass*));
    if (sfile->classes == NULL) {
        fprintf(stderr, "[-] odv_scb_open - calloc failed\n");
        odv_scb_close(sfile);
        return NULL;
    }
    memset(sfile->classes, 0, sizeof(struct ODVSCBClass*) * sfile->nbclasses);
    for (i = 0; i < sfile->nbclasses; i++) {
        class = odv_scb_parse_class(sfile);
        if (class == NULL) {
            odv_scb_close(sfile);
            return NULL;
        }
        sfile->classes[i] = class;
    }
    return sfile;
}

int odv_scb_parse_header(struct ODVSCBFile *sfile)
{
    char line[1024];

    if (sfile == NULL || sfile->file == NULL)
        return 0;
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_getheader - odv_file_readline failed\n");
        return 0;
    }
    sscanf(line, "version %f, debug %d\n", &sfile->version, &sfile->debug);
    if (sfile->version != SCB_VERSION) {
        fprintf(stderr, "[-] odv_scb_getheader - wrong SCB version\n");
        return 0;
    }
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_getheader - odv_file_readline failed\n");
        return 0;
    }
    sscanf(line, "nbOfClasses %d\n", &sfile->nbclasses);
    if (sfile->nbclasses < 0) {
        fprintf(stderr, "[-] odv_scb_getheader - negative nbOfClasses\n");
        return 0;
    }
    return 1;
}

struct ODVSCBClass *odv_scb_parse_class(struct ODVSCBFile *sfile)
{
    char line[1024];
    struct ODVSCBClass *class = NULL;
    struct ODVSCBFunction *func = NULL;
    int i;

    if (sfile == NULL || sfile->file == NULL)
        return 0;
    class = calloc(1, sizeof (struct ODVSCBClass));
    if (class == NULL) {
        fprintf(stderr, "[-] odv_scb_parse_class - calloc failed\n");
        return NULL;
    }
    memset(class, 0, sizeof (struct ODVSCBClass));
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_class - odv_file_readline failed\n");
        free(class);
        return NULL;
    }
    sscanf(line, "fileName %1023s , className %1023s\n", class->filename, class->classname);
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_class - odv_file_readline failed\n");
        free(class);
        return NULL;
    }
    sscanf(line, "nbOfVariables %d, sizeOfVariables %d\n", &class->nbofvariables, &class->sizeofvariables);
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_class - odv_file_readline failed\n");
        free(class);
        return NULL;
    }
    sscanf(line, "nbOfFunctions %d\n", &class->nboffunctions);
    if (class->nboffunctions < 0) {
        fprintf(stderr, "[-] odv_scb_parse_class - negative nboffunctions\n");
        free(class);
        return NULL;
    }
    class->funcs = calloc(class->nboffunctions, sizeof(struct ODVSCBFunction*));
    if (class->funcs == NULL) {
        fprintf(stderr, "[-] odv_scb_parse_class - calloc failed\n");
        free(class);
        return NULL;
    }
    memset(class->funcs, 0, sizeof(struct ODVSCBFunction*) * class->nboffunctions);
    for (i = 0; i < class->nboffunctions; i++) {
        func = odv_scb_parse_function(sfile);
        if (func == NULL) {
            odv_scb_clean_class(class);
            return NULL;
        }
        class->funcs[i] = func;
    }
    if (odv_scb_parse_quad(sfile, class) == 0) {
        odv_scb_clean_class(class);
        return NULL;
    }
    return class;
}

struct ODVSCBFunction *odv_scb_parse_function(struct ODVSCBFile *sfile)
{
    struct ODVSCBFunction *func = NULL;
    char line[1024];

    func = calloc(1, sizeof (struct ODVSCBFunction));
    if (func == NULL) {
        fprintf(stderr, "[-] odv_scb_parse_function - calloc failed\n");
        return NULL;
    }
    memset(func, 0, sizeof (struct ODVSCBFunction));
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_function - odv_file_readline failed\n");
        free(func);
        return NULL;
    }
    sscanf(line, "functionName %1023s , address %d, nbOfParams %d, sizeOfRetVal %d, sizeOfParams %d\n",
        func->functionname, &func->address, &func->nbofparams, &func->sizeofretval, &func->sizeofparams);
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_function - odv_file_readline failed\n");
        free(func);
        return NULL;
    }
    /* "functionParameters\n" */
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_function - odv_file_readline failed\n");
        free(func);
        return NULL;
    }
    /* "\n" */
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_function - odv_file_readline failed\n");
        free(func);
        return NULL;
    }
    sscanf(line, " sizeOfVolatile %d, sizeOfTempor %d\n", &func->sizeofvolatile, &func->sizeoftempor);
    /* "nbOfVariables %d\n" */
    return func;
}

int odv_scb_parse_quad(struct ODVSCBFile *sfile, struct ODVSCBClass *class)
{
    char line[1024];
    int i;
    size_t numberofbytesread;
    unsigned int nbofquads = 0;
    unsigned int nbofquadsread = 0;

    if (sfile == NULL || sfile->file == NULL || class == NULL)
        return 0;
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_quad - odv_file_readline failed\n");
        return 0;
    }
    sscanf(line, "nbOfQuads %d\n", &class->nbofquads);
    if (class->nbofquads < 0) {
        fprintf(stderr, "[-] odv_scb_parse_quad - negative nbofquads\n");
        return 0;
    }
    for (i = 0; i < class->nboffunctions; i++) {
        if (i != (class->nboffunctions - 1))
            nbofquads = class->funcs[i + 1]->address - class->funcs[i]->address;
        else
            nbofquads = class->nbofquads - nbofquadsread;
        class->funcs[i]->nbofquads = nbofquads;
        //if (nbofquads < 0) {
        //    fprintf(stderr, "[-] odv_scb_parse_quad - negative nbofquads\n");
        //    return 0;
        //}
        class->funcs[i]->bytecode = calloc(nbofquads * 10, sizeof (char));
        if (class->funcs[i]->bytecode == NULL) {
            fprintf(stderr, "[-] odv_scb_parse_quad - calloc failed\n");
            return 0;
        }
        numberofbytesread = odv_file_read(sfile->file, class->funcs[i]->bytecode, 10 * nbofquads);
        if (numberofbytesread != 10 * nbofquads) {
            free(class->funcs[i]->bytecode);
            class->funcs[i]->bytecode = NULL;
            fprintf(stderr, "[-] odv_scb_parse_quad - odv_file_readline failed\n");
            return 0;
        }
        nbofquadsread += nbofquads;
    }
    return 1;
}

const struct ODVSCBClass *odv_scb_get_class_byname(const struct ODVSCBFile *sfile, const char *classname)
{
    int i;

    if (sfile == NULL || sfile->classes == NULL)
        return NULL;
    for (i = 0; i < sfile->nbclasses; i++) {
        if (sfile->classes[i] && !strcmp(sfile->classes[i]->classname, classname))
            return sfile->classes[i];
    }
    return NULL;
}

const struct ODVSCBFunction *odv_scb_get_function_byname(const struct ODVSCBClass *class, const char *functionname)
{
    int i;

    if (class == NULL || class->funcs == NULL)
        return NULL;
    for (i = 0; i < class->nboffunctions; i++) {
        if (class->funcs[i] && !strcmp(class->funcs[i]->functionname, functionname))
            return class->funcs[i];
    }
    return NULL;
}

void odv_scb_info(const struct ODVSCBFile *sfile)
{
    int i;

    if (sfile == NULL)
        return;
    odv_file_info(sfile->file);
    printf("[- ODV SCB information -]\n");
    printf("version     : %f\n", sfile->version);
    printf("debug       : %d\n", sfile->debug);
    printf("nbOfClasses : %d (0x%08X)\n", sfile->nbclasses, sfile->nbclasses);
    if (sfile->classes != NULL) {
        for (i = 0; i < sfile->nbclasses; i++) {
            if (sfile->classes[i] != NULL)
                odv_scb_class_info(sfile->classes[i]);
        }
    }
    printf("[-----------------------]\n");
}

void odv_scb_function_info(const struct ODVSCBFunction *func)
{
    int i;

    if (func == NULL)
        return;
    printf("[- ODV SCB FUNCTION information -]\n");
    printf("functioname: %s\n", func->functionname);
    printf("address: %d\n", func->address);
    printf("nbofparams: %d\n", func->nbofparams);
    printf("sizeofretval: %d\n", func->sizeofretval);
    printf("sizeofparams: %d\n", func->sizeofparams);
    printf("sizeofvolatile: %d\n", func->sizeofvolatile);
    printf("sizeoftempor: %d\n", func->sizeoftempor);
    printf("nbofvariables: %d\n", func->nbofvariables);
    printf("nbofquads: %d\n", func->nbofquads);
    for (i = 0; i < func->nbofquads; i++) {
        odv_scb_diassemble((func->address) + i, func->bytecode + i * 10);
    }
    printf("\n");
}

void odv_scb_class_info(const struct ODVSCBClass *class)
{
    int i;

    if (class == NULL)
        return;
    printf("[- ODV SCB CLASS information -]\n");
    printf("filename: %s\n", class->filename);
    printf("classname: %s\n", class->classname);
    printf("nbofvariables: %d\n", class->nbofvariables);
    printf("nboffunctions: %d\n", class->nboffunctions);
    printf("nbofquads: %d\n", class->nbofquads);
    if (class->funcs != NULL) {
        for (i = 0; i < class->nboffunctions; i++) {
            if (class->funcs[i] != NULL)
                odv_scb_function_info(class->funcs[i]);
        }
    }
}

void odv_scb_clean_function(struct ODVSCBFunction *function)
{
    if (function == NULL)
        return;
    if (function->bytecode != NULL) {
        free(function->bytecode);
        function->bytecode = NULL;
    }
    free(function);
}

void odv_scb_clean_class(struct ODVSCBClass *class)
{
    int i;

    if (class == NULL)
        return;
    if (class->funcs != NULL) {
        for (i = 0; i < class->nboffunctions; i++) {
            if (class->funcs[i] != NULL) {
                odv_scb_clean_function(class->funcs[i]);
                class->funcs[i] = NULL;
            }
        }
        free(class->funcs);
        class->funcs = NULL;
    }
    free(class);
}

void odv_scb_close(struct ODVSCBFile *sfile)
{
    int i;

    if (sfile == NULL)
        return;
    if (sfile->file != NULL)
        odv_file_close(sfile->file);
    if (sfile->classes != NULL) {
        for (i = 0; i < sfile->nbclasses; i++) {
            if (sfile->classes[i] != NULL) {
                odv_scb_clean_class(sfile->classes[i]);
                sfile->classes[i] = NULL;
            }
        }
        free(sfile->classes);
        sfile->classes = NULL;
    }
    free(sfile);
}
