#ifndef OPENDV_SCB_MANAGER_H
#define OPENDV_SCB_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ODVFile.h"

#define SCB_VERSION 1.0

struct ODVSCBFunction
{
    char functionname[1024];
    unsigned int address;
    unsigned int nbofparams;
    unsigned int sizeofretval;
    unsigned int sizeofparams;
    unsigned int sizeofvolatile;
    unsigned int sizeoftempor;
    unsigned int nbofvariables;
    unsigned int nbofquads;
    unsigned char *bytecode;
};

struct ODVSCBClass
{
    char filename[1024];
    char classname[1024];
    unsigned int nbofvariables;
    unsigned int sizeofvariables;
    unsigned int nboffunctions;
    unsigned int nbofquads;

    struct ODVSCBFunction **funcs;
};

struct ODVSCBFile
{
    struct ODVFile *file;
    float version;
    int debug;
    unsigned int nbclasses;
    struct ODVSCBClass **classes;
};

struct ODVSCBFile *odv_scb_open(char *filename);
void odv_scb_close(struct ODVSCBFile *sfile);
int odv_scb_parse_header(struct ODVSCBFile *sfile);

void odv_scb_info(struct ODVSCBFile *sfile);
void odv_scb_class_info(struct ODVSCBClass *class);
void odv_scb_function_info(struct ODVSCBFunction *func);

struct ODVSCBClass *odv_scb_parse_class(struct ODVSCBFile *sfile);
// int odv_scb_parse_class(struct ODVSCBFile *sfile);
struct ODVSCBFunction *odv_scb_parse_function(struct ODVSCBFile *sfile);
// int odv_scb_parse_function(struct ODVSCBFile *sfile);

#endif /* OPENDV_SCB_MANAGER_H */
