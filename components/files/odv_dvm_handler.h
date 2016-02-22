#ifndef OPENDV_DVM_HANDLER_H
#define OPENDV_DVM_HANDLER_H

#include <stdlib.h>
#include <stdio.h>

#include "odv_file.h"
#include "odv_image.h"

struct ODVDvm
{
    struct ODVFile *file;
    struct ODVImage *img;
};

struct ODVDvm *odv_dvm_open(const char *filename);
void odv_dvm_info(const struct ODVDvm *dvm);
void odv_dvm_close(struct ODVDvm *dvm);

#endif /* OPENDV_DVM_HANDLER_H */
