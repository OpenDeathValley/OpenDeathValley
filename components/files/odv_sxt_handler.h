#ifndef OPENDV_SXT_HANDLER_H
#define OPENDV_SXT_HANDLER_H

#include <stdlib.h>
#include <stdio.h>

#include "odv_file.h"
#include "odv_image.h"

struct ODVSxt
{
    struct ODVFile *file;
    struct ODVImage *img;
};

struct ODVSxt *odv_sxt_open(const char *filename);
void odv_sxt_info(const struct ODVSxt *sxt);
void odv_sxt_close(struct ODVSxt *sxt);

#endif /* OPENDV_SXT_HANDLER_H */
