#include "odv_test.h"
#include "odv_resource_handler.h"

void odv_test_resource(void)
{
    struct ODVResourceFile *rfile = NULL;

    rfile = odv_resource_open("Expressions.res");
    if (rfile == NULL) {
        return;
    }
    odv_resource_info(rfile);
    odv_resource_close(rfile);
}

int main(void)
{
    printf("[+] Launching test\n");
    odv_test_resource();
    return 0;
}
