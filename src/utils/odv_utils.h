#ifndef OPENDV_UTILS_H
#define OPENDV_UTILS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef WINDOWS

#define snprintf _snprintf

#endif

void hex_dump(void *data, int size);

#endif /* OPENDV_UTILS_H */