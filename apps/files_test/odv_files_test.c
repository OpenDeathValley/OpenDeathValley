#include "odv_files_test.h"

struct ODVFileType file_types[ODV_MAX_FILE_TYPE] = {
    {"dvd", "dvd file (*.dvd)", odv_test_dvd},
    {"dvf", "dvf file (*.dvf)", odv_test_dvf},
    {"dvm", "map (*.dvm)", odv_test_dvm},
    {"fnt", "font file (*.fnt)", odv_test_fnt},
    {"fxg", "Sound bank (*.fxg)", odv_test_fxg},
    {"map", "map interface (*.map)", odv_test_map},
    {"res", "ressource file (*.res)", odv_test_resource},
    {"scb", "script file (*.scb)", odv_test_script},
    {"sxt", "screen win/loose (*.sxt)", odv_test_sxt}
};

void odv_test_resource(struct ODVFileTest *filetest)
{
    struct ODVResourceFile *rfile = NULL;

    fprintf(stderr, "[+] odv_resource_open = %s\n", filetest->filename);
    rfile = odv_resource_open(filetest->filename);
    if (rfile == NULL)
        return;
    odv_resource_info(rfile);
    odv_resource_close(rfile);
}

void odv_test_script(struct ODVFileTest *filetest)
{
    struct ODVSCBFile *sfile = NULL;
    const struct ODVSCBClass *class = NULL;
    const struct ODVSCBFunction *func = NULL;

    fprintf(stderr, "[+] odv_scb_open = %s\n", filetest->filename);
    sfile = odv_scb_open(filetest->filename);
    if (sfile == NULL)
        return;
    class = odv_scb_get_class_byname(sfile, "__1___Tir_au_co5440da0");
    if (class == NULL)
        fprintf(stderr, "[-] Can't find class \"__1___Tir_au_co5440da0\"\n");
    else {
        func = odv_scb_get_function_byname(class, "EnterZone");
        if (func == NULL)
            fprintf(stderr, "[-] Can't find function \"EnterZone\"\n");
    }
    odv_scb_info(sfile);
    odv_scb_close(sfile);
}

void odv_test_dvd(struct ODVFileTest *filetest)
{
    struct ODVDDvdFile *dfile = NULL;

    fprintf(stderr, "[+] odv_test_dvd = %s\n", filetest->filename);
    dfile = odv_dvd_open(filetest->filename);
    if (dfile == NULL)
        return;
    odv_dvd_info(dfile);
    odv_dvd_close(dfile);
}


void odv_test_fxg(struct ODVFileTest *filetest)
{
    struct ODVSoundFXGFile *sfile = NULL;

    fprintf(stderr, "[+] odv_scb_open = %s\n", filetest->filename);
    sfile = odv_fxg_open(filetest->filename);
    if (sfile == NULL)
        return;
    odv_fxg_close(sfile);
}

void odv_test_map(struct ODVFileTest *filetest)
{
    struct ODVMap *mfile = NULL;

    fprintf(stderr, "[+] odv_map_open = %s\n", filetest->filename);
    mfile = odv_map_open(filetest->filename);
    if (mfile == NULL)
        return;
    odv_map_info(mfile);
    odv_map_close(mfile);
}

void odv_test_dvm(struct ODVFileTest *filetest)
{
    struct ODVDvm *dvm = NULL;

    fprintf(stderr, "[+] odv_dvm_open = %s\n", filetest->filename);
    dvm = odv_dvm_open(filetest->filename);
    if (dvm == NULL)
        return;
    odv_dvm_info(dvm);
    odv_dvm_close(dvm);
}

void odv_test_sxt(struct ODVFileTest *filetest)
{
    struct ODVSxt *sxt = NULL;

    fprintf(stderr, "[+] odv_sxt_open = %s\n", filetest->filename);
    sxt = odv_sxt_open(filetest->filename);
    if (sxt == NULL)
        return;
    odv_sxt_info(sxt);
    odv_sxt_close(sxt);
}

void odv_test_fnt(struct ODVFileTest *filetest)
{
    struct ODVFnt *fnt = NULL;

    fprintf(stderr, "[+] odv_fnt_open = %s\n", filetest->filename);
    fnt = odv_fnt_open(filetest->filename);
    if (fnt == NULL)
        return;
    odv_fnt_info(fnt);
    odv_fnt_close(fnt);
}

void odv_test_dvf(struct ODVFileTest *filetest)
{
    struct ODVDvf *dvf = NULL;
    unsigned short min_x = 0;
    unsigned short min_y = 0;
    unsigned short wx = 0;
    unsigned short hy = 0;

    fprintf(stderr, "[+] odv_dvf_open = %s\n", filetest->filename);
    dvf = odv_dvf_open(filetest->filename);
    if (dvf == NULL) {
        return;
    }
    if (filetest->info) {
        odv_dvf_info(dvf);
    }
    if (filetest->extract) {
        for (unsigned short i = 0; i < dvf->nb_profiles; i++) {
            for (unsigned short j = 0; j < (unsigned short)(dvf->profiles[i]->nb_perspectives * dvf->profiles[i]->nb_animations); j++) {
                odv_dvf_get_frame_min_x_y(dvf->profiles[i]->animations[j], &min_x, &min_y);
                odv_dvf_get_frame_max_wx_hy(dvf, dvf->profiles[i]->animations[j], &wx, &hy);
                for (unsigned short k = 0; k < dvf->profiles[i]->animations[j]->nb_frames; k++) {
                    char bmp_filepath[MAX_PATH];
#ifdef WINDOWS
                    snprintf(bmp_filepath, MAX_PATH - 1, "%s\\%s_%s_%04d.bmp",filetest->output, dvf->profiles[i]->name, dvf->profiles[i]->animations[j]->animation_name + 1, k);
#else
                    snprintf(bmp_filepath, MAX_PATH - 1, "%s/%s_%s_%04d.bmp",filetest->output, dvf->profiles[i]->name, dvf->profiles[i]->animations[j]->animation_name + 1, k);
#endif
                    odv_image_to_bmp_ex(dvf->sprites[dvf->profiles[i]->animations[j]->frames[k]->sprite_id], bmp_filepath, wx - min_x, hy - min_y, dvf->profiles[i]->animations[j]->frames[k]->coordinate_x - min_x, dvf->profiles[i]->animations[j]->frames[k]->coordinate_y - min_y);

                }
            }
        }
    }
    odv_dvf_close(dvf);
}

void print_usage(const char *argv0)
{
    printf("Usage: %s [ OPTIONS ] FILE\n\n", argv0);
    printf("Options:\n");
    printf("    -h, --help         display this help and exit\n");
    printf("    -e, --extract      extract files (if possible) ; requires output folder to be set\n");
    printf("    -i, --info         print information\n");
    printf("    -o, --output=STR   extract files to STR folder\n");
    printf("    -t, --type=STR     set file type to STR\n");
    printf("    -v,                set verbose mode\n");
    printf("    Available types:\n");
    for (int i = 0; i < ODV_MAX_FILE_TYPE; i++) {
        printf("        %s : %s\n", file_types[i].type, file_types[i].description);
    }
    exit(EXIT_FAILURE);
}

int parse_arguments(int argc, char *argv[], struct ODVFileTest *filetest)
{
    int pos_arg;

    for (pos_arg = 1; pos_arg < argc; pos_arg++) {
        if (argv[pos_arg][0] != '-') {
            break;
        }
        size_t length_argv = strlen(argv[pos_arg]);
        for (size_t pos_argv = 0; pos_argv < length_argv; pos_argv++) {
            switch (argv[pos_arg][pos_argv]) {
                case '-':
                    if (pos_argv > 0 && argv[pos_arg][pos_argv-1] == '-') {
                        if (0) {
                            ARG_GETS_BOOL('v', filetest->verbose)
                        }
                        else if ARG_GETL_BOOL("info", 'i', filetest->info)
                        else if ARG_GETL_BOOL("extract", 'e', filetest->extract)
                        else if ARG_GETL_VAL("type", 't', filetest->type)
                        else if ARG_GETL_VAL("output", 'o', filetest->output)
                        else if ARG_LONG("help") case 'h': case '?': {
                            print_usage(argv[0]);
                        }
                        else { default:
                            fprintf(stderr,
                                    "%s: invalid option '%s'\n"
                                    "Try '%s --help' for more information.\n",
                                    argv[0], argv[pos_arg], argv[0]);
                            return 1;
                        }
                }
            }
        }
    }
    if ((pos_arg + 1) > argc) {
        fprintf(stderr,
            "missing argument FILE\n"
            "Try '%s --help' for more information.\n",
            argv[0]);
        return 1;
    }
    filetest->filename = argv[pos_arg];
    return 0;
}

int validate_arguments(char *argv0, struct ODVFileTest *filetest)
{
    if (filetest->extract && filetest->output == NULL) {
        fprintf(stderr,
            "%s: missing output folder\n"
            "Try '%s --help' for more information.\n",
            argv0,
            argv0);
        return 1;
    }
    if (filetest->output && file_exists(filetest->output)) {
        fprintf(stderr,
            "%s: output folder %s doesn't exist\n"
            "Try '%s --help' for more information.\n",
            argv0,
            filetest->output,
            argv0);
        return 1;
    }
    if (filetest->output && is_regular_file(filetest->output)) {
        fprintf(stderr,
            "%s: output folder %s is not a directory\n"
            "Try '%s --help' for more information.\n",
            argv0,
            filetest->output,
            argv0);
        return 1;
    }
    if (filetest->output && is_folder_writable(filetest->output)) {
        fprintf(stderr,
            "%s: output folder %s is not writtable\n"
            "Try '%s --help' for more information.\n",
            argv0,
            filetest->output,
            argv0);
        return 1;
    }
    if (filetest->type == NULL) {
        fprintf(stderr,
            "%s: file type is missing\n"
            "Try '%s --help' for more information.\n",
            argv0,
            argv0);
        return 1;
    }
    for (int i = 0; i < ODV_MAX_FILE_TYPE; i++) {
        if (!strcmp(file_types[i].type, filetest->type)) {
            return 0;
        }
    }
    fprintf(stderr,
        "%s: file type is incorrect\n"
        "Try '%s --help' for more information.\n",
        argv0,
        argv0);
    return 1;
}

int main(int argc, char *argv[])
{
    struct ODVFileTest filetest = {0};

    if (argc < 2) {
        print_usage(argv[0]);
    }
    if (parse_arguments(argc, argv, &filetest)) {
        exit(EXIT_FAILURE);
    }
    if (validate_arguments(argv[0], &filetest)) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < ODV_MAX_FILE_TYPE; i++) {
        if (!strcmp(file_types[i].type, filetest.type)) {
            file_types[i].func_ptr(&filetest);
            break;
        }
    }
    return 0;
}
