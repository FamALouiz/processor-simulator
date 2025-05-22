cmake_minimum_required(VERSION 3.10)

# Project name
project(ProcessorSimulator)

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
include_directories(${CMAKE_SOURCE_DIR}/libs/util)

# Source files for the main executable
set(MAIN_SOURCES
    ${CMAKE_SOURCE_DIR}/libs/util/path.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/mem_manager.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/word.c
    ${CMAKE_SOURCE_DIR}/libs/file_parser/file_parser.c
    ${CMAKE_SOURCE_DIR}/libs/parser/parser.c
    ${CMAKE_SOURCE_DIR}/libs/datapath/datapath.c
    ${CMAKE_SOURCE_DIR}/libs/parser/functions.c
    ${CMAKE_SOURCE_DIR}/libs/config_loader/config_loader.c
    ${CMAKE_SOURCE_DIR}/src/main.c
)

# Add the main executable
add_executable(processor-simulator ${MAIN_SOURCES})

# Library components for testing
set(LIB_SOURCES
    ${CMAKE_SOURCE_DIR}/libs/util/path.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/mem_manager.c
    ${CMAKE_SOURCE_DIR}/libs/parser/functions.c
    ${CMAKE_SOURCE_DIR}/libs/config_loader/config_loader.c
    ${CMAKE_SOURCE_DIR}/libs/file_parser/file_parser.c
)

# Unit tests
set(UNIT_TEST_MEM_MANAGER_SOURCES 
    ${CMAKE_SOURCE_DIR}/test/unit/test_mem_manager.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/mem_manager.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
)

set(UNIT_TEST_PARSER_SOURCES 
    ${CMAKE_SOURCE_DIR}/test/unit/test_parser.c
    ${CMAKE_SOURCE_DIR}/libs/parser/functions.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/mem_manager.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
)

set(UNIT_TEST_PARSE_INSTRUCTION_SOURCES 
    ${CMAKE_SOURCE_DIR}/test/unit/test_parse_instruction.c
    ${CMAKE_SOURCE_DIR}/libs/parser/functions.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/mem_manager.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
)

set(UNIT_TEST_BRANCH_INSTRUCTIONS_SOURCES 
    ${CMAKE_SOURCE_DIR}/test/unit/test_branch_instructions.c
    ${CMAKE_SOURCE_DIR}/libs/parser/functions.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/mem_manager.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
)

set(UNIT_TEST_PATH_UTILS_SOURCES 
    ${CMAKE_SOURCE_DIR}/test/unit/test_path_utils.c
    ${CMAKE_SOURCE_DIR}/libs/util/path.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
)

set(UNIT_TEST_CONFIG_LOADER_SOURCES 
    ${CMAKE_SOURCE_DIR}/test/unit/test_config_loader.c
    ${CMAKE_SOURCE_DIR}/libs/config_loader/config_loader.c
    ${CMAKE_SOURCE_DIR}/libs/util/path.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
)

set(UNIT_TEST_FILE_PARSER_SOURCES 
    ${CMAKE_SOURCE_DIR}/test/unit/test_file_parser.c
    ${CMAKE_SOURCE_DIR}/libs/file_parser/file_parser.c
    ${CMAKE_SOURCE_DIR}/libs/util/path.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/mem_manager.c
)

set(UNIT_TEST_INSTRUCTIONS_SOURCES 
    ${CMAKE_SOURCE_DIR}/test/unit/test_instructions.c
    ${CMAKE_SOURCE_DIR}/libs/parser/functions.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/mem_manager.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
)

# Functional tests
set(FUNCTIONAL_TEST_PROCESSOR_PIPELINE_SOURCES 
    ${CMAKE_SOURCE_DIR}/test/functional/test_processor_pipeline.c
    ${LIB_SOURCES}
)

set(FUNCTIONAL_TEST_FULL_PIPELINE_SOURCES 
    ${CMAKE_SOURCE_DIR}/test/functional/test_full_pipeline.c
    ${LIB_SOURCES}
)

# Add the unit test executables
add_executable(test_mem_manager ${UNIT_TEST_MEM_MANAGER_SOURCES})
add_executable(test_parser ${UNIT_TEST_PARSER_SOURCES})
add_executable(test_parse_instruction ${UNIT_TEST_PARSE_INSTRUCTION_SOURCES})
add_executable(test_branch_instructions ${UNIT_TEST_BRANCH_INSTRUCTIONS_SOURCES})
add_executable(test_path_utils ${UNIT_TEST_PATH_UTILS_SOURCES})
add_executable(test_config_loader ${UNIT_TEST_CONFIG_LOADER_SOURCES})
add_executable(test_file_parser ${UNIT_TEST_FILE_PARSER_SOURCES})
add_executable(test_instructions ${UNIT_TEST_INSTRUCTIONS_SOURCES})

# Add the functional test executables
add_executable(test_processor_pipeline ${FUNCTIONAL_TEST_PROCESSOR_PIPELINE_SOURCES})
add_executable(test_full_pipeline ${FUNCTIONAL_TEST_FULL_PIPELINE_SOURCES})

# Add a custom target to run all tests
add_custom_target(run_tests
    COMMAND test_mem_manager
    COMMAND test_parser
    COMMAND test_parse_instruction
    COMMAND test_branch_instructions
    COMMAND test_path_utils
    COMMAND test_config_loader
    COMMAND test_file_parser
    COMMAND test_instructions
    COMMAND test_processor_pipeline
    COMMAND test_full_pipeline
    DEPENDS 
        test_mem_manager
        test_parser
        test_parse_instruction
        test_branch_instructions
        test_path_utils
        test_config_loader
        test_file_parser
        test_instructions
        test_processor_pipeline
        test_full_pipeline
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)