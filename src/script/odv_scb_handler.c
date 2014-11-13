#include "odv_scb_handler.h"

char *extern_func[] = {"sub_5E2AF0", "sub_5E2B00", "sub_5E2B10", "sub_5E2B30",
    "sub_5E2B40", "sub_5E2B50", "sub_5E2B70", "sub_5E2B80", "sub_5E2B90",
    "sub_5E2BB0", "sub_5E2BC0", "sub_5E2BD0", "sub_5E2BE0", "sub_5E2BF0",
    "sub_5E2C00", "sub_5E2C20", "sub_5E2C30", "sub_5E2C40", "sub_5E2C50",
    "sub_5E2C60", "sub_5E2C70", "sub_5E2C80", "sub_5E2C90", "sub_5E2CA0",
    "sub_5E2CB0", "sub_5E2CC0", "sub_5E2CD0", "sub_5E2CE0", "sub_5E2CF0",
    "sub_5E2D00", "sub_5E2D10", "sub_5E2D20", "sub_5E2D30", "sub_5E2D40",
    "sub_5E2D50", "sub_5E2D60", "sub_5E2D70", "sub_5E2D90", "sub_5E2DB0",
    "sub_5E2DD0", "sub_5E2DE0", "sub_5E2DF0", "sub_5E2E00", "sub_5E2E10",
    "sub_5E2E20", "sub_5E2E40", "sub_5E2E60", "sub_5E2E80", "sub_5E2E90",
    "sub_5E2EB0", "sub_5E2EC0", "sub_5E2EE0", "sub_5E2EF0", "sub_5E2F10",
    "sub_5E2F20", "sub_5E2F40", "sub_5E2F60", "sub_5E2F80", "sub_5E2FA0",
    "sub_5E2FB0", "sub_5E2FD0", "sub_5E2FF0", "sub_5E3000", "sub_5E3010",
    "sub_5E3020", "sub_5E3040", "sub_5E3050", "sub_5E3060", "sub_5E3070",
    "sub_5E3090", "sub_5E30A0", "sub_5E30B0", "sub_5E30C0", "sub_5E30D0",
    "sub_5E30E0", "sub_5E30F0", "sub_5E3100", "sub_5E3110", "sub_5E3120",
    "sub_5E3130", "sub_5E3140", "sub_5E3150", "sub_5E3170", "sub_5E3180",
    "sub_5E3190", "sub_5E31B0", "sub_5E31D0", "sub_5E31E0", "sub_5E31F0",
    "sub_5E3200", "sub_5E3220", "sub_5E3240", "sub_5E3260", "sub_5E3280",
    "sub_5E32A0", "sub_5E32C0", "sub_5E32E0", "sub_5E3300", "sub_5E3320",
    "sub_5E3330", "sub_5E3340", "sub_5E3350", "sub_5E3360", "sub_5E3370",
    "sub_5E3390", "sub_5E33A0", "sub_5E33C0", "sub_5E33E0", "sub_5E33F0",
    "sub_5E3400", "sub_5E3410", "sub_5E3420", "sub_5E3430", "sub_5E3440",
    "sub_5E3450", "sub_5E3460", "sub_5E3470", "sub_5E3480", "sub_5E3490",
    "sub_5E34B0", "sub_5E34D0", "sub_5E34F0", "sub_5E3510", "sub_5E3530",
    "sub_5E3540", "sub_5E3550", "sub_5E3570", "sub_5E3580", "sub_5E3590",
    "sub_5E35A0", "sub_5E35B0", "sub_5E35C0", "sub_5E35E0", "sub_5E3600",
    "sub_5E3620", "sub_5E3630", "sub_5E3640", "sub_5E3650", "sub_5E3660",
    "sub_5E3680", "sub_5E36A0", "sub_5E36C0", "sub_5E36E0", "sub_5E36F0",
    "sub_5E3700", "sub_5E3710", "sub_5E3720", "sub_5E3730", "sub_5E3740",
    "sub_5E3750", "sub_5E3760", "sub_5E3770", "sub_5E3790", "sub_5E37B0",
    "sub_5E37D0", "sub_5E37F0", "sub_5E3800", "sub_5E3820", "sub_5E3830",
    "sub_5E3850", "sub_5E3860", "sub_5E3870", "sub_5E3890", "sub_5E38B0",
    "sub_5E38D0", "sub_5E38F0", "sub_5E3900", "sub_5E3920", "sub_5E3930",
    "sub_5E3940", "sub_5E3960", "sub_5E3970", "sub_5E3980", "sub_5E3990",
    "sub_5E39A0", "sub_5E39C0", "sub_5E39E0", "sub_5E3A00", "sub_5E3A10",
    "sub_5E3A20", "sub_5E3A40", "sub_5E3A50", "sub_5E3A60", "sub_5E3A70",
    "sub_5E3A80", "sub_5E3A90", "sub_5E3AB0", "sub_5E3AD0", "sub_5E3AE0",
    "sub_5E3AF0", "sub_5E3B20", "sub_5E3B40", "sub_5E3B50", "sub_5E3B60",
    "sub_5E3B70", "sub_5E3B80", "sub_5E3BA0", "sub_5E3BB0", "sub_5E3BC0",
    "sub_5E3BD0" };

struct ODVSCBFile *odv_scb_open(const char *filename)
{
    struct ODVFile *file = NULL;
    struct ODVSCBFile *sfile = NULL;
    struct ODVSCBClass *class = NULL;
    unsigned int i;

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
    unsigned int i;

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

void odv_scb_info(struct ODVSCBFile *sfile)
{
    unsigned int i;

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

void odv_scb_print_opcode_bytes(unsigned char *buf)
{
    unsigned int i;

    for (i = 0; i < 10; i++) {
        printf("%02X ", buf[i]);
    }
}

void odv_scb_operation_flag_info(unsigned short flag)
{
    if (flag) {
        switch (flag) {
            case 0x4000:
                printf("f: 0x4000");
                break;

            case 0x8000:
                printf("f: 0x8000 (NS_VOLATILE_VAR)");
                break;

            case 0xC000:
                printf("f: 0xC000 (NS_TEMP_VAR)");
                break;

            default:
                fprintf(stderr, "[-] unknow flag : %04X\n", flag);
        }
    }
    else {
        printf("f: 0x0000");
    }
}

void odv_scb_diassemble(unsigned int addr, unsigned char *buf)
{
    unsigned char opcode;
    unsigned short sval_0;
    unsigned short flag_0;
    unsigned short sval_1;
    unsigned short flag_1;
    unsigned short sval_2;
    unsigned short flag_2;
    unsigned int ival_0;

    opcode = buf[0];

    switch (opcode) {
        case 0x00:
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x00 - Operation not allowed\n");
            break;

        case 0x01:
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x01 - NOP\n");
            break;

        case 0x02:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x02 - sval_0: 0x%04X ; ");
            odv_scb_operation_flag_info(flag_0);
            printf("\n");
            break;

        case 0x03:
            sval_0 = *(unsigned short*)(buf + 1);
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x03 - sval_0 (SIZEOFVOLATILE): 0x%04X ; sval_1 (SIZEOFTEMPOR): 0x%04X\n", sval_0, sval_1);
            break;

        case 0x04:
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x04 - VMCore::EndFunction\n");
            break;

        case 0x07:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x07 - ??? - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf("\n");
            break;

        case 0x08:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x08 - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; ival_0: 0x%08X", ival_0);
            printf("\n");
            break;

        case 0x0B:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x0B - PUSH ARGS - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf("\n");
            break;

        case 0x0C:
            ival_0 = *(unsigned int*)(buf + 1);
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x0C - Call external %d method: %s\n", ival_0, extern_func[ival_0]);
            break;

        case 0x0D:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x0D - STORE RESULT - sval_0: 0x%04X ; flag_0: 0x%4X\n", sval_0, flag_0);
            break;

        case 0x0E:
            ival_0 = *(unsigned int*)(buf + 1);
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x0E - JMP - %08X\n", ival_0);
            break;

        case 0x0F:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x0F - JE - sval_0: 0x%04X ; flag_0: 0x%4X ; ival_0: 0x%08X\n", sval_0, flag_0, ival_0);
            break;

        case 0x11:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x11 - ??? - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; sval_1: 0x%04X ; ", sval_1);
            odv_scb_operation_flag_info(flag_1);
            printf("\n");
            break;

        case 0x13:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x13 - LOAD IMM32 - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; ival_0: 0x%08X", ival_0);
            printf("\n");
            break;

        case 0x14:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            ival_0 = *(unsigned int*)(buf + 1 + 4);
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x14 - LOAD IMM32 - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; ival_0: 0x%08X", ival_0);
            printf("\n");
            break;

        case 0x15:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x15 - NS SUB - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; sval_1: 0x%04X ; ", sval_1);
            odv_scb_operation_flag_info(flag_1);
            printf("\n");
            break;

        case 0x1A:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x1A - SUB DWORD - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; sval_1: 0x%04X ; ", sval_1);
            odv_scb_operation_flag_info(flag_1);
            printf(" ; sval_2: 0x%04X ; ", sval_2);
            odv_scb_operation_flag_info(flag_2);
            printf("\n");
            break;

        case 0x24:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x25 - GT DWORD - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; sval_1: 0x%04X ; ", sval_1);
            odv_scb_operation_flag_info(flag_1);
            printf(" ; sval_2: 0x%04X ; ", sval_2);
            odv_scb_operation_flag_info(flag_2);
            printf("\n");
            break;

        case 0x25:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x25 - NEQ DWORD - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; sval_1: 0x%04X ; ", sval_1);
            odv_scb_operation_flag_info(flag_1);
            printf(" ; sval_2: 0x%04X ; ", sval_2);
            odv_scb_operation_flag_info(flag_2);
            printf("\n");
            break;

        case 0x26:
            sval_0 = *(unsigned short*)(buf + 1);
            flag_0 = sval_0 & 0xC000;
            sval_0 = sval_0 & 0x3FFF;
            sval_1 = *(unsigned short*)(buf + 1 + 2);
            flag_1 = sval_1 & 0xC000;
            sval_1 = sval_1 & 0x3FFF;
            sval_2 = *(unsigned short*)(buf + 1 + 4);
            flag_2 = sval_2 & 0xC000;
            sval_2 = sval_2 & 0x3FFF;
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t0x26 - EQ DWORD - sval_0: 0x%04X ; ", sval_0);
            odv_scb_operation_flag_info(flag_0);
            printf(" ; sval_1: 0x%04X ; ", sval_1);
            odv_scb_operation_flag_info(flag_1);
            printf(" ; sval_2: 0x%04X ; ", sval_2);
            odv_scb_operation_flag_info(flag_2);
            printf("\n");
            break;

        default:
            printf("%08X: ", addr);
            odv_scb_print_opcode_bytes(buf);
            printf("\t%02X - FUU - %08X %08X\n", opcode, *(unsigned int*)(buf + 1), *(unsigned int*)(buf + 1 + 4));
    }
}

void odv_scb_function_info(struct ODVSCBFunction *func)
{
    unsigned int i;

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

void odv_scb_class_info(struct ODVSCBClass *class)
{
    unsigned int i;

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
    unsigned int i;

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
