#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/utilities/logger.h"

struct loggerConfig {
    char filePath[512];
    long long bufferSize;
};

enum LoggerConfigKey {
    LOGGER_FILE_PATH,
    LOGGER_BUFFER_SIZE,
    UNKNOWN_OPTION
};

struct ConfigEntry {
    enum LoggerConfigKey key;
    char* name;
};

static const struct ConfigEntry configEntries[] = {
    {LOGGER_FILE_PATH, "logFile"},
    {LOGGER_BUFFER_SIZE, "logBufferSize"}
};

static enum LoggerConfigKey getKeyFromName(const char* name) {
    for (int i = 0; i < sizeof(configEntries) / sizeof(struct ConfigEntry); i++) {
        if (strcmp(configEntries[i].name, name) == 0) {
            return configEntries[i].key;
        }
    }
    return UNKNOWN_OPTION;
}

static long long parseBufferSize(char* sizeString) {
    char *endPointer;
    long long strValue = strtol(sizeString, &endPointer, 10);

    while (isspace(*endPointer)) endPointer++;

    if (strcmp(endPointer, "KB") == 0) {
        strValue *= 1024;
    } else if (strcmp(endPointer, "MB") == 0) {
        strValue *= 1024 * 1024;
    } else if (strcmp(endPointer, "GB") == 0) {
        strValue *= 1024 * 1024 * 1024;
    }
    return strValue;
}

static void addConfig(struct loggerConfig* config, enum LoggerConfigKey key, char* value) {
    switch (key) {
        case LOGGER_FILE_PATH:
            strcpy(config->filePath, value);
            break;
        case LOGGER_BUFFER_SIZE:
            config->bufferSize = parseBufferSize(value);
            break;
        default:
            break;
    }
}

static struct loggerConfig readConfigInformation() {
    struct loggerConfig loggerConfig = {0};

    FILE* configFile = fopen("./variables/logger.conf", "r");
    if (configFile != NULL) {
        char configBuffer[512];

        while (fgets(configBuffer, sizeof(configBuffer), configFile) != NULL) {
            char* splitChar = strchr(configBuffer, '=');
            if (splitChar == NULL) continue;
            *splitChar = '\0';

            char* key = configBuffer;
            char* value = splitChar + 1;

            enum LoggerConfigKey configKey = getKeyFromName(key);
            addConfig(&loggerConfig, configKey, value);
        }

        fclose(configFile);
    }
    return loggerConfig;
}

static void startup() {
    struct loggerConfig loggerConfig = readConfigInformation();
    printf("Logger config file: %s\n", loggerConfig.filePath);
    printf("Logger buffersize: %lld\n", loggerConfig.bufferSize);
}



int main(void) {
    printf("Hello, World!\n");

    startup();
    logger_log(INFO, "hello world");

    return 0;
}
