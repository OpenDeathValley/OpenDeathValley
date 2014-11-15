#ifndef OPENDV_RESOURCE_HANDLER_H
#define OPENDV_RESOURCE_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "odv_file.h"

#include "odv_resource.h"
#include "odv_resource_wave.h"
#include "odv_resource_text.h"

struct ODVResourceFile *odv_resource_open(const char *filename);
int odv_resource_read_header(struct ODVResourceFile *rfile);

struct ODVResourceEntry *odv_resource_parse_entry(struct ODVResourceFile *rfile);

void odv_resource_close(struct ODVResourceFile *rfile);

int odv_resource_get_type_index(struct ODVResourceFile *rfile, unsigned int index);

/* INFO / DBG */

void odv_resource_info(const struct ODVResourceFile *rfile);
/* void odv_resource_headerinfo(const struct ODVResourceHeader *re);
void odv_resourcetype_headerinfo(const struct ODVResourceTypeHeader *re); */

#endif /* OPENDV_RESOURCE_HANDLER_H */
