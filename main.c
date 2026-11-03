#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "configuration/paths.h"
#include "src/utilities/logger.h"

struct loggerConfig {
    char filePath[512];
    enum LogLevel logLevel;
};

enum LoggerConfigKey {
    LOGGER_FILE_PATH,
    LOG_LEVEL,
    UNKNOWN_OPTION
};

struct ConfigEntry {
    enum LoggerConfigKey key;
    char* name;
};

static const struct ConfigEntry configEntries[] = {
    {LOGGER_FILE_PATH, "logFile"},
    {LOG_LEVEL, "logLevel"}
};

static enum LoggerConfigKey getKeyFromName(const char* name) {
    for (int i = 0; i < sizeof(configEntries) / sizeof(struct ConfigEntry); i++) {
        if (strcmp(configEntries[i].name, name) == 0) {
            return configEntries[i].key;
        }
    }
    return UNKNOWN_OPTION;
}

static enum LogLevel getLogLevelFromName(const char* name) {
    for (int i = 0; i < sizeof(logMappings) / sizeof(struct LogLevelMap); i++) {
        if (strcmp(logMappings[i].name, name) == 0) {
            return logMappings[i].key;
        }
    }
    return ERROR;
}

static void addConfig(struct loggerConfig* config, enum LoggerConfigKey key, char* value) {
    size_t len = strlen(value);
    if (value[len-1] == '\n') value[len-1] = '\0';
    switch (key) {
        case LOGGER_FILE_PATH:
            strcpy(config->filePath, value);
            break;
        case LOG_LEVEL:
            config->logLevel = getLogLevelFromName(value);
            break;
        default:
            break;
    }
}

static struct loggerConfig readConfigInformation() {
    struct loggerConfig loggerConfig = {0};
    FILE* configFile = fopen( BINARY_ROOT "/configuration/logger.conf", "r");
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
    printf("Logger LogLevel: %d\n", loggerConfig.logLevel);
}



int main(void) {
    printf("Hello, World!\n");

    startup();
    logger_log(INFO, "hello world");

    return 0;
}
