#ifndef OPENDV_SCB_DISASSEMBLER_H
#define OPENDV_SCB_DISASSEMBLER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "odv_file.h"

#define NB_EXTERNAL_FUNC 200
#define NB_ARGS_MAX      5

struct ODVExternalFuncArgs
{
    unsigned int size;
    const char *type;
};

struct ODVExternalFunction
{
    const char *name;
    unsigned int nbarguments;
    struct ODVExternalFuncArgs funcargs[NB_ARGS_MAX];
    const char *description;
};

void odv_scb_print_opcode_bytes(const unsigned char *buf);
char *odv_scb_operation_flag_info(unsigned short flag);
void odv_scb_diassemble(unsigned int addr, const unsigned char *buf);

#endif /* OPENDV_SCB_DISASSEMBLER_H */
