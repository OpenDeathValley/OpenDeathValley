#ifndef OPENDV_SCB_DISASSEMBLER_H
#define OPENDV_SCB_DISASSEMBLER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "odv_file.h"

#define NB_EXTERNAL_FUNC 200

void odv_scb_print_opcode_bytes(const unsigned char *buf);
void odv_scb_operation_flag_info(unsigned short flag);
void odv_scb_diassemble(unsigned int addr, const unsigned char *buf);

#endif /* OPENDV_SCB_DISASSEMBLER_H */
