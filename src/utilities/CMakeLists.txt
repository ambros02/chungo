add_library(utilsLib STATIC)

target_sources(utilsLib
    PRIVATE logger.c
    PUBLIC
        FILE_SET HEADERS
        FILES
            logger.h
)