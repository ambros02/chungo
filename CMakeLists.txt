cmake_minimum_required(VERSION 4.2)
project(chungo LANGUAGES C VERSION 1.1.1)

set(CMAKE_C_STANDARD 99)

# shared files
configure_file(configuration/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/configuration/version.h)
configure_file(configuration/paths.h.in ${CMAKE_CURRENT_BINARY_DIR}/configuration/paths.h)

# client / server specific
configure_file(configuration/server/logger.conf ${CMAKE_CURRENT_BINARY_DIR}/configuration/server/logger.conf COPYONLY)
configure_file(configuration/client/logger.conf ${CMAKE_CURRENT_BINARY_DIR}/configuration/client/logger.conf COPYONLY)


add_subdirectory(src/shared/utilities)

add_executable(chungoClient)
add_executable(chungoServer)

target_include_directories(chungoClient PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(chungoServer PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_sources(chungoClient
    PRIVATE
        src/client/main.c
)

target_sources(chungoServer
        PRIVATE
        src/server/main.c
)

target_link_libraries(chungoClient PRIVATE utilsLib)
target_link_libraries(chungoServer PRIVATE utilsLib)