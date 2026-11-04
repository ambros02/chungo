add_library(utilsLib STATIC)

target_include_directories(utilsLib PRIVATE
    ${CMAKE_BINARY_DIR}
)

target_sources(utilsLib
    PRIVATE logger.c
    PUBLIC
        FILE_SET HEADERS
        FILES
        logger.h
)