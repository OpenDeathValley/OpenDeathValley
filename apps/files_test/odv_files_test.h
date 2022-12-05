#ifndef OPENDV_TEST_H
#define OPENDV_TEST_H

#include "odv_resource_handler.h"
#include "odv_scb_handler.h"
#include "odv_fxg_handler.h"
#include "odv_dvd_handler.h"
#include "odv_map_handler.h"
#include "odv_dvm_handler.h"
#include "odv_sxt_handler.h"
#include "odv_fnt_handler.h"
#include "odv_dvf_handler.h"

#define ODV_MAX_FILE_TYPE 9

struct ODVFileTest
{
    int info;
    int verbose;
    int extract;
    char *type;
    char *output;
    char *filename;
};

struct ODVFileType {
    const char *type;
    const char *description;
    void (*func_ptr)(struct ODVFileTest*);
};

void odv_test_resource(struct ODVFileTest *filetest);
void odv_test_script(struct ODVFileTest *filetest);
void odv_test_dvd(struct ODVFileTest *filetest);
void odv_test_fxg(struct ODVFileTest *filetest);
void odv_test_map(struct ODVFileTest *filetest);
void odv_test_dvm(struct ODVFileTest *filetest);
void odv_test_sxt(struct ODVFileTest *filetest);
void odv_test_fnt(struct ODVFileTest *filetest);
void odv_test_dvf(struct ODVFileTest *filetest);

#endif /* OPENDV_TEST_H */