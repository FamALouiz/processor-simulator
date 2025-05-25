cmake_minimum_required(VERSION 3.10)

# Project name
project(ProcessorSimulator)

# Suppress compiler warnings
if(MSVC)
    add_compile_options(/w)
else()
    add_compile_options(-w)
endif()

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include/log)
include_directories(${CMAKE_SOURCE_DIR}/include/memory_management)
include_directories(${CMAKE_SOURCE_DIR}/include/file_parser)
include_directories(${CMAKE_SOURCE_DIR}/include/datapath)
include_directories(${CMAKE_SOURCE_DIR}/include/config_loader)
include_directories(${CMAKE_SOURCE_DIR}/include/parser)
include_directories(${CMAKE_SOURCE_DIR}/include/util)

# Source files for the main executable
set(MAIN_SOURCES
    ${CMAKE_SOURCE_DIR}/libs/util/path.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/mem_manager.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/word.c
    ${CMAKE_SOURCE_DIR}/libs/file_parser/file_parser.c
    ${CMAKE_SOURCE_DIR}/libs/parser/word_parser.c
    ${CMAKE_SOURCE_DIR}/libs/datapath/datapath.c
    ${CMAKE_SOURCE_DIR}/libs/parser/functions.c
    ${CMAKE_SOURCE_DIR}/libs/config_loader/config_loader.c
    ${CMAKE_SOURCE_DIR}/src/main.c
)

# Add the main executable
add_executable(processor-simulator ${MAIN_SOURCES})