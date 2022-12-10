#ifndef OPENDV_RESOURCE_CUR_H
#define OPENDV_RESOURCE_CUR_H

#include "odv_resource.h"

#define CUR_SIGNATURE 0x20525543

struct ODVResourceCur
{
    unsigned int useless;
    unsigned short tick_count_redraw;
    unsigned short hit_point_y;
    unsigned short hit_point_x;
    unsigned short tick_count_redraw_per_image;
    int nbentry;
    struct ODVImageMap *imgmap;
};

void *odv_resource_parse_cur(struct ODVResourceFile *rfile);
void odv_resource_cur_info(const struct ODVResourceCur *cur);
void odv_resource_cur_extract(const struct ODVResourceCur *picc, const char *filename, const char *output, unsigned int id);
void odv_resource_clean_cur(struct ODVResourceCur *cur);

#endif /* OPENDV_RESOURCE_CUR_H */
