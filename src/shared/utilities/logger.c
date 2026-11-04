#include "logger.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "configuration/paths.h"
#include <stdarg.h>

static struct runTimeLoggerConfig runTimeConfig = {0};

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

struct loggerConfig readConfigInformation(char* projectName) {
    struct loggerConfig loggerConfig = {0};

    char configFileString[2048];
    snprintf(configFileString, sizeof(configFileString), "%s/configuration/%s/logger.conf", BINARY_ROOT, projectName);

    FILE* configFile = fopen(configFileString , "r");
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


int setupLoger(char* projectName) {
    struct loggerConfig loggerConfig = readConfigInformation(projectName);
    runTimeConfig.logFile = fopen(loggerConfig.filePath, "a");
    if (runTimeConfig.logFile == NULL) return -1;

    runTimeConfig.logLevel = loggerConfig.logLevel;
    runTimeConfig.messageCount = 0;

    logger_log(INFO, "logger started with filepath %s", loggerConfig.filePath);

    return 0;
}

int closeLoger() {
    fclose(runTimeConfig.logFile);
    return 0;
}

void logger_log(enum LogLevel logLevel, const char* message, ...) {
    if (logLevel >= runTimeConfig.logLevel) {
        char messageBuffer[2048];

        va_list args;
        va_start(args, message);

        vsnprintf(messageBuffer, sizeof(messageBuffer), message, args);

        runTimeConfig.messageCount++;

        time_t now = time(NULL);
        struct tm timeInfo;
        localtime_r(&now, &timeInfo);

        char timestamp[32];
        strftime(timestamp, sizeof(timestamp),"%Y-%m-%d %H:%M:%S", &timeInfo);
    fprintf(runTimeConfig.logFile, "[%s] [%s] %s\n", timestamp, logMappings[logLevel].name, messageBuffer);
    }

    if (runTimeConfig.messageCount == 20) {
        fflush(runTimeConfig.logFile);
        runTimeConfig.messageCount = 0;
    }
}