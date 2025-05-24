cmake_minimum_required(VERSION 3.10)
project(ProcessorSimulator C)

# → Use C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# → Gather all of your .c files in one variable
set(SOURCES
    ${CMAKE_SOURCE_DIR}/libs/util/path.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/mem_manager.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/word.c
    ${CMAKE_SOURCE_DIR}/libs/file_parser/file_parser.c
    ${CMAKE_SOURCE_DIR}/libs/parser/word_parser.c
    ${CMAKE_SOURCE_DIR}/libs/datapath/datapath.c
    ${CMAKE_SOURCE_DIR}/libs/parser/functions.c
    ${CMAKE_SOURCE_DIR}/libs/config_loader/config_loader.c
    ${CMAKE_SOURCE_DIR}/src/gui_main.c
)

# → Define your executable (WIN32 makes it a GUI app, omit if you want console)
add_executable(processor-simulator
    WIN32
    ${SOURCES}
)

# → Pull in your include-dirs only for this target
target_include_directories(processor-simulator
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include/log
        ${CMAKE_SOURCE_DIR}/include/memory_management
        ${CMAKE_SOURCE_DIR}/include/file_parser
        ${CMAKE_SOURCE_DIR}/include/datapath
        ${CMAKE_SOURCE_DIR}/include/config_loader
        ${CMAKE_SOURCE_DIR}/include/parser
)

# → Define common Win32 macros
target_compile_definitions(processor-simulator
    PRIVATE
        WIN32_LEAN_AND_MEAN
        UNICODE
        _UNICODE
)

# → Only on Windows, link the system libraries you need
if(WIN32)
    target_link_libraries(processor-simulator
        PRIVATE
            kernel32
            user32
            gdi32
            advapi32
            shell32
    )
endif()
