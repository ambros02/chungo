#ifndef CHUNGO_LOGGER_H
#define CHUNGO_LOGGER_H


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

static const struct LogLevelMap logMappings[] = {
    {DEBUG, "DEBUG"},
    {INFO, "INFO"},
    {WARNING, "WARNING"},
    {ERROR, "ERROR"},
    {FATAL, "FATAL"}
};






void logger_log(enum LogLevel log_level, const char* message);


#endif //CHUNGO_LOGGER_H
