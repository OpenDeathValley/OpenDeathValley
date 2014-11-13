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
    sfile = (struct ODVSCBFile*)malloc(sizeof (struct ODVSCBFile));
    if (sfile == NULL) {
        fprintf(stderr, "[-] odv_scb_open - malloc failed\n");
        odv_file_close(file);
        return NULL;
    }
    memset(sfile, 0, sizeof (struct ODVSCBFile));
    sfile->file = file;
    if (odv_scb_parse_header(sfile) == 0) {
        odv_file_close(sfile->file);
        free(sfile);
        return NULL;
    }
    sfile->classes = (struct ODVSCBClass**)malloc(sizeof(struct ODVSCBClass*) * sfile->nbclasses);
    if (sfile->classes == NULL) {
        fprintf(stderr, "[-] odv_scb_open - malloc failed\n");
        odv_file_close(sfile->file);
        free(sfile);
        return NULL;
    }
    memset(sfile->classes, 0, sizeof(struct ODVSCBClass*) * sfile->nbclasses);
    for (i = 0; i < sfile->nbclasses; i++) {
        class = odv_scb_parse_class(sfile);
        if (class == NULL) {
            odv_file_close(sfile->file);
            free(sfile);
            /* TODO: free all previous one */
            return NULL;
        }
        sfile->classes[i] = class;
    }
    return sfile;
}

struct ODVSCBFunction *odv_scb_parse_function(struct ODVSCBFile *sfile)
{
    struct ODVSCBFunction *func = NULL;
    char line[1024];
    /*
    char functionname[1024];
    unsigned int address;
    unsigned int nbofparams;
    unsigned int sizeofretval;
    unsigned int sizeofparams;
    unsigned int sizeofvolatile;
    unsigned int sizeoftempor;
    unsigned int nbofvariables;
    */

    func = (struct ODVSCBFunction*)malloc(sizeof (struct ODVSCBFunction));
    if (func == NULL) {
        fprintf(stderr, "[-] odv_scb_parse_function - malloc failed\n");
        return NULL;
    }
    memset(func, 0, sizeof (struct ODVSCBFunction));
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_classes - odv_file_readline failed\n");
        free(func);
        return NULL;
    }
    sscanf(line, "functionName %1023s , address %d, nbOfParams %d, sizeOfRetVal %d, sizeOfParams %d\n",
        func->functionname, &func->address, &func->nbofparams, &func->sizeofretval, &func->sizeofparams);
    //printf("functionname: %s\n", func->functionname);
    //printf("address     : %d\n", func->address);
    //printf("nbofparams  : %d\n", func->nbofparams);
    //printf("sizeofretval: %d\n", func->sizeofretval);
    //printf("sizeofparams: %d\n", func->sizeofparams);
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_classes - odv_file_readline failed\n");
        free(func);
        return NULL;
    }
    // "functionParameters\n"
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_classes - odv_file_readline failed\n");
        free(func);
        return NULL;
    }
    // "\n"
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_classes - odv_file_readline failed\n");
        free(func);
        return NULL;
    }
    sscanf(line, " sizeOfVolatile %d, sizeOfTempor %d\n", &func->sizeofvolatile, &func->sizeoftempor);
    //printf("sizeofvolatile: %d\n", func->sizeofvolatile);
    //printf("sizeoftempor  : %d\n", func->sizeoftempor);
    //"nbOfVariables %d\n"
    return func;
}

struct ODVSCBClass *odv_scb_parse_class(struct ODVSCBFile *sfile)
{
    char line[1024];
    /*char filename[1024];
    char classname[1024];
    unsigned int nbofvariables;
    unsigned int sizeofvariables;
    unsigned int nboffunctions;
    unsigned int nbofquads;*/
    struct ODVSCBClass *class = NULL;
    struct ODVSCBFunction *func = NULL;
    int i;

    int numberofbytesread;

    //unsigned char unk_byte_00;
    //unsigned long long unk_qword_00;

    int nbofquads = 0;
    int nbofquadsread = 0;

    if (sfile == NULL || sfile->file == NULL)
        return 0;
    class = (struct ODVSCBClass*)malloc(sizeof (struct ODVSCBClass));
    if (class == NULL) {
        fprintf(stderr, "[-] odv_scb_parse_class - malloc failed\n");
        return NULL;
    }
    memset(class, 0, sizeof (struct ODVSCBClass));
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_classes - odv_file_readline failed\n");
        return 0;
    }
    sscanf(line, "fileName %1023s , className %1023s\n", class->filename, class->classname);
    //printf("filename : %s\n", class->filename);
    //printf("classname: %s\n", class->classname);
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_classes - odv_file_readline failed\n");
        return 0;
    }
    sscanf(line, "nbOfVariables %d, sizeOfVariables %d\n", &class->nbofvariables, &class->sizeofvariables);
    //printf("nbofvariables : %d\n", class->nbofvariables);
    //printf("sizeofvariables: %d\n", class->sizeofvariables);
    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_classes - odv_file_readline failed\n");
        return 0;
    }
    sscanf(line, "nbOfFunctions %d\n", &class->nboffunctions);
    //printf("nboffunctions: %d\n", class->nboffunctions);

    class->funcs = (struct ODVSCBFunction**)malloc(sizeof(struct ODVSCBFunction*) * class->nboffunctions);
    if (class->funcs == NULL) {
        fprintf(stderr, "[-] odv_scb_parse_classes - malloc failed\n");
        free(class);
        return NULL;
    }

    for (i = 0; i < class->nboffunctions; i++) {
        func = odv_scb_parse_function(sfile);
        if (func == NULL) {
            /* TODO: free all previous one */
            free(class);
            return NULL;
        }
        class->funcs[i] = func;
    }

    if (odv_file_readline(sfile->file, line, sizeof (line) - 1) == 0) {
        fprintf(stderr, "[-] odv_scb_parse_classes - odv_file_readline failed\n");
        return 0;
    }
    sscanf(line, "nbOfQuads %d\n", &class->nbofquads);
    //printf("nbofquads : %d\n", class->nbofquads);
    for (i = 0; i < class->nboffunctions; i++) {
        if (i != (class->nboffunctions - 1)) {
            nbofquads = class->funcs[i + 1]->address - class->funcs[i]->address;
            //printf("nbofquads: %d\n", nbofquads);
            class->funcs[i]->nbofquads = nbofquads;
            class->funcs[i]->bytecode = malloc((sizeof (char) * nbofquads) * 10);
            if (class->funcs[i]->bytecode == NULL) {
                fprintf(stderr, "[-] odv_scb_parse_classes - malloc failed\n");
                /* TODO: clean everything */
                return NULL;
            }
            numberofbytesread = odv_file_read(sfile->file, class->funcs[i]->bytecode, 10 * nbofquads);
            if (numberofbytesread != 10 * nbofquads) {
                fprintf(stderr, "[-] odv_scb_parse_classes - odv_file_readline failed\n");
                return NULL;
            }
            nbofquadsread += nbofquads;
        }
        else {
            nbofquads = class->nbofquads - nbofquadsread;
            //printf("nbofquads: %d\n", nbofquads);
            class->funcs[i]->nbofquads = nbofquads;
            class->funcs[i]->bytecode = malloc((sizeof (char) * nbofquads) * 10);
            if (class->funcs[i]->bytecode == NULL) {
                fprintf(stderr, "[-] odv_scb_parse_classes - malloc failed\n");
                /* TODO: clean everything */
                return NULL;
            }
            numberofbytesread = odv_file_read(sfile->file, class->funcs[i]->bytecode, 10 * nbofquads);
            if (numberofbytesread != 10 * nbofquads) {
                fprintf(stderr, "[-] odv_scb_parse_classes - odv_file_readline failed\n");
                return NULL;
            }
        }

    }
    /* for (i = 0; i < class->nbofquads; i++) {
        numberofbytesread = odv_file_read(sfile->file, &unk_byte_00, 1);
        if (numberofbytesread != 1) {
            fprintf(stderr, "[-] odv_scb_parse_classes - odv_file_readline failed\n");
            return 0;
        }
        printf("unk_byte_00  : 0x%02X\n", unk_byte_00);
        numberofbytesread = odv_file_read(sfile->file, &unk_qword_00, 8);
        if (numberofbytesread != 8) {
            fprintf(stderr, "[-] odv_scb_parse_classes - odv_file_readline failed\n");
            return 0;
        }
        printf("unk_qword_00 : 0x%016llX\n", unk_qword_00);
        sfile->file->pos += 1;
    } */
    return class;
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
    return 1;
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
    if (sfile->classes) {
        for (i = 0; i < sfile->nbclasses; i++) {
            if (sfile->classes[i])
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
        //odv_scb_diassemble((func->address * 0x10) + (i * 0x10), func->bytecode + i * 10);
        odv_scb_diassemble((func->address) + i, func->bytecode + i * 10);
        //printf("%02X ", func->bytecode[i * 10]);
    }
    printf("\n");
    /* unsigned char *bytecode; */
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
    if (class->funcs) {
        for (i = 0; i < class->nboffunctions; i++) {
            if (class->funcs[i])
                odv_scb_function_info(class->funcs[i]);
        }
    }
}

void odv_scb_close(struct ODVSCBFile *sfile)
{
    int i;

    if (sfile == NULL)
        return;
    if (sfile->file != NULL)
        odv_file_close(sfile->file);
    /* TODO: more clean */
    if (sfile->classes) {
        for (i = 0; i < sfile->nbclasses; i++) {
            if (sfile->classes[i]) {
                free(sfile->classes[i]);
            }
        }
        free(sfile->classes);
    }
    free(sfile);
}
