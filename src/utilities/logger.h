#ifndef CHUNGO_LOGGER_H
#define CHUNGO_LOGGER_H

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
};



void logger_log(enum LogLevel log_level, const char* message);


#endif //CHUNGO_LOGGER_H
