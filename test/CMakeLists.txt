# Test configuration
include_directories(${CMAKE_SOURCE_DIR}/test)

# Libs for all tests
set(TEST_LIBS
    ${CMAKE_SOURCE_DIR}/libs/util/path.c
    ${CMAKE_SOURCE_DIR}/libs/log/logger.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/mem_manager.c
    ${CMAKE_SOURCE_DIR}/libs/memory_management/word.c
    ${CMAKE_SOURCE_DIR}/libs/file_parser/file_parser.c
    ${CMAKE_SOURCE_DIR}/libs/parser/word_parser.c
    ${CMAKE_SOURCE_DIR}/libs/datapath/datapath.c
    ${CMAKE_SOURCE_DIR}/libs/parser/functions.c
    ${CMAKE_SOURCE_DIR}/libs/config_loader/config_loader.c
    ${UNITY_SOURCES}
)

# Config loader tests
set(TEST_CONFIG_LOADER_SOURCES
    ${CMAKE_SOURCE_DIR}/test/unit/config_loader/test_config_load.c
    ${CMAKE_SOURCE_DIR}/test/unit/config_loader/test_config_loader_runner.c
    ${TEST_LIBS}
)
add_executable(test_config_loader ${TEST_CONFIG_LOADER_SOURCES})
add_test(NAME test_config_loader COMMAND test_config_loader)

# File parser tests
set(TEST_FILE_PARSER_SOURCES
    ${CMAKE_SOURCE_DIR}/test/unit/file_parser/test_file_parser.c
    ${CMAKE_SOURCE_DIR}/test/unit/file_parser/test_file_parser_runner.c
    ${TEST_LIBS}
)
add_executable(test_file_parser ${TEST_FILE_PARSER_SOURCES})
add_test(NAME test_file_parser COMMAND test_file_parser)

# Memory management tests
set(TEST_MEM_MANAGER_SOURCES
    ${CMAKE_SOURCE_DIR}/test/unit/memory_management/test_mem_manager.c
    ${CMAKE_SOURCE_DIR}/test/unit/memory_management/test_mem_manager_runner.c
    ${TEST_LIBS}
)
add_executable(test_mem_manager ${TEST_MEM_MANAGER_SOURCES})
add_test(NAME test_mem_manager COMMAND test_mem_manager)

# Path utility tests
set(TEST_PATH_UTILS_SOURCES
    ${CMAKE_SOURCE_DIR}/test/unit/util/test_path.c
    ${CMAKE_SOURCE_DIR}/test/unit/util/test_path_runner.c
    ${TEST_LIBS}
)
add_executable(test_path_utils ${TEST_PATH_UTILS_SOURCES})
add_test(NAME test_path_utils COMMAND test_path_utils)

# Word parser tests
set(TEST_WORD_PARSER_SOURCES
    ${CMAKE_SOURCE_DIR}/test/unit/parser/test_word_parser_add.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser/test_word_parser_sub.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser/test_word_parser_mul.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser/test_word_parser_and.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser/test_word_parser_lsl.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser/test_word_parser_lsr.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser/test_word_parser_movi.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser/test_word_parser_runner.c

    ${TEST_LIBS}
)
add_executable(test_word_parser ${TEST_WORD_PARSER_SOURCES})
add_test(NAME test_word_parser COMMAND test_word_parser)

# word parser test 2
set(TEST_WORD_PARSER_SOURCES_2    
    ${CMAKE_SOURCE_DIR}/test/unit/parser_2/test_word_parser_jeq_not_equal.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser_2/test_word_parser_jeq.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser_2/test_word_parser_xori.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser_2/test_word_parser_movr.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser_2/test_word_parser_movm.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser_2/test_word_parser_jmp.c
    ${CMAKE_SOURCE_DIR}/test/unit/parser_2/test_word_parser_runner_2.c
    ${TEST_LIBS}
)
add_executable(test_word_parser_2 ${TEST_WORD_PARSER_SOURCES_2})
add_test(NAME test_word_parser_2 COMMAND test_word_parser_2)



# Functional - Instruction pipeline tests
set(TEST_INSTRUCTION_PIPELINE_SOURCES
    ${CMAKE_SOURCE_DIR}/test/functional/test_instruction_pipeline.c
    ${CMAKE_SOURCE_DIR}/test/functional/test_instruction_pipeline_runner.c
    ${TEST_LIBS}
)
add_executable(test_instruction_pipeline ${TEST_INSTRUCTION_PIPELINE_SOURCES})
add_test(NAME test_instruction_pipeline COMMAND test_instruction_pipeline)

# Functional - Branch instructions tests
set(TEST_BRANCH_INSTRUCTIONS_SOURCES
    ${CMAKE_SOURCE_DIR}/test/functional/test_branch_instructions.c
    ${CMAKE_SOURCE_DIR}/test/functional/test_branch_instructions_runner.c
    ${TEST_LIBS}
)
add_executable(test_branch_instructions ${TEST_BRANCH_INSTRUCTIONS_SOURCES})
add_test(NAME test_branch_instructions COMMAND test_branch_instructions)

# Functional - Memory operations tests
set(TEST_MEMORY_OPERATIONS_SOURCES
    ${CMAKE_SOURCE_DIR}/test/functional/test_memory_operations.c
    ${CMAKE_SOURCE_DIR}/test/functional/test_memory_operations_runner.c
    ${TEST_LIBS}
)
add_executable(test_memory_operations ${TEST_MEMORY_OPERATIONS_SOURCES})
add_test(NAME test_memory_operations COMMAND test_memory_operations)

# Add a target to run all tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS 
        test_config_loader
        test_file_parser
        test_mem_manager
        test_path_utils
        test_word_parser
        test_instructions
        test_instruction_pipeline
        test_branch_instructions
        test_memory_operations
)
