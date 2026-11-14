#ifndef CHUNGO_LOGGER_H

#define CHUNGO_LOGGER_H
#define LOG(log_level, message, ...) logger_log(__FILE__, __LINE__, log_level, message, ##__VA_ARGS__)

#include <stdio.h>

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
};

struct LogLevelMap {
    enum LogLevel key;
    char* name;
};

struct loggerConfig {
    char filePath[512];
    enum LogLevel logLevel;
};

struct runTimeLoggerConfig {
    FILE* logFile;
    enum LogLevel logLevel;
    size_t messageCount;
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


static const struct LogLevelMap logMappings[] = {
    {DEBUG, "DEBUG"},
    {INFO, "INFO"},
    {WARNING, "WARNING"},
    {ERROR, "ERROR"},
    {FATAL, "FATAL"}
};


struct loggerConfig readConfigInformation();

int setupLoger(char* projectName);

void logger_log(const char* file, int lineNumber, enum LogLevel log_level, const char* message, ...);
void logCrash(const char* callStack, const char* file, int line, const char* message, ...);

#endif //CHUNGO_LOGGER_H
