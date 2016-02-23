#include "odv_files_test.h"

void odv_test_resource(const char *filename)
{
    struct ODVResourceFile *rfile = NULL;

    fprintf(stderr, "[+] odv_resource_open = %s\n", filename);
    rfile = odv_resource_open(filename);
    if (rfile == NULL)
        return;
    odv_resource_info(rfile);
    odv_resource_close(rfile);
}

void odv_test_script(const char *filename)
{
    struct ODVSCBFile *sfile = NULL;
    const struct ODVSCBClass *class = NULL;
    const struct ODVSCBFunction *func = NULL;

    fprintf(stderr, "[+] odv_scb_open = %s\n", filename);
    sfile = odv_scb_open(filename);
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

void odv_test_dvd(const char *filename)
{
    struct ODVDDvdFile *dfile = NULL;

    fprintf(stderr, "[+] odv_test_dvd = %s\n", filename);
    dfile = odv_dvd_open(filename);
    if (dfile == NULL)
        return;
    odv_dvd_info(dfile);
    odv_dvd_close(dfile);
}


void odv_test_fxg(const char *filename)
{
    struct ODVSoundFXGFile *sfile = NULL;

    fprintf(stderr, "[+] odv_scb_open = %s\n", filename);
    sfile = odv_fxg_open(filename);
    if (sfile == NULL)
        return;
    odv_fxg_close(sfile);
}

void odv_test_map(const char *filename)
{
    struct ODVMap *mfile = NULL;

    fprintf(stderr, "[+] odv_map_open = %s\n", filename);
    mfile = odv_map_open(filename);
    if (mfile == NULL)
        return;
    odv_map_info(mfile);
    odv_map_close(mfile);
}

void odv_test_dvm(const char *filename)
{
    struct ODVDvm *dvm = NULL;

    fprintf(stderr, "[+] odv_dvm_open = %s\n", filename);
    dvm = odv_dvm_open(filename);
    if (dvm == NULL)
        return;
    odv_dvm_info(dvm);
    odv_dvm_close(dvm);
}

void odv_test_sxt(const char *filename)
{
    struct ODVSxt *sxt = NULL;

    fprintf(stderr, "[+] odv_sxt_open = %s\n", filename);
    sxt = odv_sxt_open(filename);
    if (sxt == NULL)
        return;
    odv_sxt_info(sxt);
    odv_sxt_close(sxt);
}

void odv_test_fnt(const char *filename)
{
    struct ODVFnt *fnt = NULL;

    fprintf(stderr, "[+] odv_fnt_open = %s\n", filename);
    fnt = odv_fnt_open(filename);
    if (fnt == NULL)
        return;
    odv_fnt_info(fnt);
    odv_fnt_close(fnt);
}

void help(void)
{
    printf("OPTION:\n");
    printf("\t-r: resource file (*.res)\n");
    printf("\t-s: script file (*.scb)\n");
    printf("\t-d: dvd file (*.dvd)\n");
    printf("\t-f: Sound bank (*.fxg)\n");
    printf("\t-m: map interface (*.map)\n");
    printf("\t-v: map (*.dvm)\n");
    printf("\t-x: screen win/loose (*.sxt)\n");
    printf("\t-n: font (*.fnt)\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "[-] Usage: %s OPTION FILE\n", argv[0]);
        help();
    }
    if (argv[1][0] != '-') {
        help();
    }
    switch (argv[1][1]) {
        case 'r':
            odv_test_resource(argv[2]);
            break;
        case 's':
            odv_test_script(argv[2]);
            break;
        case 'd':
            odv_test_dvd(argv[2]);
            break;
        case 'f':
            odv_test_fxg(argv[2]);
            break;
        case 'm':
            odv_test_map(argv[2]);
            break;
        case 'v':
            odv_test_dvm(argv[2]);
            break;
        case 'x':
            odv_test_sxt(argv[2]);
            break;
        case 'n':
            odv_test_fnt(argv[2]);
            break;
        default:
            help();
    }
    return 0;
}
