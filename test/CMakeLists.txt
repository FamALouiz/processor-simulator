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

# # File parser tests
# set(TEST_FILE_PARSER_SOURCES
#     ${TEST_LIBS}
# )
# add_executable(test_file_parser ${TEST_FILE_PARSER_SOURCES})
# add_test(NAME test_file_parser COMMAND test_file_parser)

# # Memory management tests
# set(TEST_MEM_MANAGER_SOURCES
#     ${TEST_LIBS}
# )
# add_executable(test_mem_manager ${TEST_MEM_MANAGER_SOURCES})
# add_test(NAME test_mem_manager COMMAND test_mem_manager)

# # Path utility tests
# set(TEST_PATH_UTILS_SOURCES
#     ${TEST_LIBS}
# )
# add_executable(test_path_utils ${TEST_PATH_UTILS_SOURCES})
# add_test(NAME test_path_utils COMMAND test_path_utils)

# # Instructions tests
# set(TEST_INSTRUCTIONS_SOURCES
#     ${TEST_LIBS}
# )
# add_executable(test_instructions ${TEST_INSTRUCTIONS_SOURCES})
# add_test(NAME test_instructions COMMAND test_instructions)

# # Branch instructions tests
# set(TEST_BRANCH_INSTRUCTIONS_SOURCES
#     ${TEST_LIBS}
# )
# add_executable(test_branch_instructions ${TEST_BRANCH_INSTRUCTIONS_SOURCES})
# add_test(NAME test_branch_instructions COMMAND test_branch_instructions)

# # Processor pipeline tests
# set(TEST_PROCESSOR_PIPELINE_SOURCES
#     ${TEST_LIBS}
# )
# add_executable(test_processor_pipeline ${TEST_PROCESSOR_PIPELINE_SOURCES})
# add_test(NAME test_processor_pipeline COMMAND test_processor_pipeline)

# # Full pipeline tests
# set(TEST_FULL_PIPELINE_SOURCES
#     ${TEST_LIBS}
# )
# add_executable(test_full_pipeline ${TEST_FULL_PIPELINE_SOURCES})
# add_test(NAME test_full_pipeline COMMAND test_full_pipeline)

# # Full pipeline unit tests
# set(TEST_FULL_PIPELINE_UNIT_SOURCES
#     ${TEST_LIBS}
# )
# add_executable(test_full_pipeline_unit ${TEST_FULL_PIPELINE_UNIT_SOURCES})
# add_test(NAME test_full_pipeline_unit COMMAND test_full_pipeline_unit)

# Add a target to run all tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS 
        test_config_loader
        # test_file_parser
        # test_mem_manager
        # test_path_utils
        # test_instructions
        # test_branch_instructions
        # test_processor_pipeline
        # test_full_pipeline
        # test_full_pipeline_unit
)
