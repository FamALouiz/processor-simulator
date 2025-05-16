cmake_minimum_required(VERSION 3.10)

# Project name
project(ProcessorSimulator)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include/log)
include_directories(${CMAKE_SOURCE_DIR}/include/memory_management)

# Source files for the main executable
set(MAIN_SOURCES
    ${CMAKE_SOURCE_DIR}/libs/util/path.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/mem_manger.c
    ${CMAKE_SOURCE_DIR}/libs/parser/parser.c
    ${CMAKE_SOURCE_DIR}/libs/parser/preParser.c
    ${CMAKE_SOURCE_DIR}/src/main.c
)

# Add the main executable
add_executable(processor-simulator ${MAIN_SOURCES})