#include "odv_test.h"

void odv_test_resource(const char *filename)
{
    struct ODVResourceFile *rfile = NULL;

    rfile = odv_resource_open(filename);
    if (rfile == NULL) {
        return;
    }
    odv_resource_info(rfile);
    odv_resource_close(rfile);
}

void odv_test_script(const char *filename)
{
    struct ODVSCBFile *sfile = NULL;

    fprintf(stderr, "[+] odv_scb_open = %s\n", filename);
    sfile = odv_scb_open(filename);
    if (sfile == NULL) {
        return;
    }
    odv_scb_info(sfile);
    odv_scb_close(sfile);
}

void help(void)
{
    printf("OPTION:\n");
    printf("\t-r: resource file (*.res)\n");
    printf("\t-s: script file (*.scb)\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "[-] Usage: %s OPTION FILE\n", argv[1]);
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
        default:
            help();
    }
    return 0;
}
