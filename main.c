#include <stdio.h>

#include "src/utilities/logger.h"

int main(void) {
    printf("Hello, World!\n");

    logger_log(INFO, "hello world");

    return 0;
}
