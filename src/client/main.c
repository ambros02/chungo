#include "../shared/utilities/logger.h"
#include <stdio.h>

#include <stdlib.h>

static void startup() {
    int success = setupLoger("client");
    if (success != 0) {
        printf("Failed to setup logger");
        exit(1);
    }
}



int main(void) {
    startup();
    return 0;
}
