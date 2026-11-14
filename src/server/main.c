#include "../shared/utilities/logger.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "communication/socket.h"
#include "communication/connectionQueue.h"

static void startup() {
    int success = setupLoger("server");
    if (success != 0) {
        printf("Failed to setup logger");
        exit(1);
    }
    openServerSocket();
}



static void runServer() {

    /*
        struct ConnectionQueue* queue = queue_init();
        free(queue);
     *
     */
}


int main(void) {
    startup();
    LOG(INFO, "Server started");
    return 0;
}
