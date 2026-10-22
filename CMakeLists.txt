cmake_minimum_required(VERSION 4.2)
project(chungo LANGUAGES C VERSION 1.1.1)

set(CMAKE_C_STANDARD 99)

configure_file(configuration/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/variables/version.h)

add_subdirectory(src/utilities)


add_executable(chungo)

target_sources(chungo
    PRIVATE
        main.c
)

target_link_libraries(chungo PRIVATE utilsLib)