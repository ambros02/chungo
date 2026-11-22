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
        src/client/communication/socket.c
        src/shared/protocol/Task.h
        src/shared/protocol/chuProtocol.h
        src/shared/protocol/chuProtocol.c
)

target_sources(chungoServer
        PRIVATE
        src/server/main.c
        src/server/communication/socket.c
        src/server/communication/taskQueue.h
        src/server/communication/taskQueue.c
        src/server/communication/clientList.h
        src/server/communication/clientList.c
        src/shared/protocol/Task.h
)

target_compile_options(chungoServer PRIVATE
    "-fmacro-prefix-map=${CMAKE_SOURCE_DIR}/=./"
)

target_compile_options(chungoClient PRIVATE
        "-fmacro-prefix-map=${CMAKE_SOURCE_DIR}/=./"
)

target_link_libraries(chungoClient PRIVATE utilsLib)
target_link_libraries(chungoServer PRIVATE utilsLib)