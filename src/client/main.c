#include "../shared/utilities/logger.h"
#include <stdio.h>

#include <stdlib.h>

#include "communication/socket.h"

static void startup() {
    int success = setupLoger("client");
    if (success != 0) {
        printf("Failed to setup logger");
        exit(1);
    }

    openClientSocket();
}



int main(void) {
    startup();

    return 0;
}
