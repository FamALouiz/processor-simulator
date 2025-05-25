#include "unity.h"
#include "datapath.h"
#include "file_parser.h"
#include "mem_manager.h"
#include "word.h"
#include "config_loader.h"
#include <stdio.h>

#define TEST_PROGRAM_PATH "test/data/functional_test_program.asm"

void setUp(void)
{
    load_properties("config/InstructionMappings.config");
    memset(&main_memory, 0, sizeof(memory_interface));
    initProgramCounter(0);
}

void tearDown(void)
{
}

void write_test_program(void)
{
    FILE *file = fopen(TEST_PROGRAM_PATH, "w");

    if (file == NULL)
    {
        TEST_FAIL_MESSAGE("Failed to create test assembly file");
    }

    fprintf(file, "# Simple test program\n");
    fprintf(file, "MOVI R1, 10\n");
    fprintf(file, "MOVI R2, 20\n");
    fprintf(file, "ADD R3, R1, R2\n");
    fprintf(file, "SUB R4, R2, R1\n");
    fprintf(file, "MUL R5, R3, R4\n");

    fclose(file);
}

void remove_test_program(void)
{
    remove(TEST_PROGRAM_PATH);
}

void test_full_instruction_pipeline(void)
{
    write_test_program();

    parse_and_encode(TEST_PROGRAM_PATH);

    pipeline_stage *pipeline = initializeStages();
    runPipeline(pipeline);

    word r1_result, r2_result, r3_result, r4_result, r5_result;
    unsigned int r1_value, r2_value, r3_value, r4_value, r5_value;

    reg_read(R1, &r1_result);
    reg_read(R2, &r2_result);
    reg_read(R3, &r3_result);
    reg_read(R4, &r4_result);
    reg_read(R5, &r5_result);

    word_to_int(&r1_result, &r1_value);
    word_to_int(&r2_result, &r2_value);
    word_to_int(&r3_result, &r3_value);
    word_to_int(&r4_result, &r4_value);
    word_to_int(&r5_result, &r5_value);

    // Verify R1 = 10, R2 = 20
    TEST_ASSERT_EQUAL_INT(10, r1_value);
    TEST_ASSERT_EQUAL_INT(20, r2_value);

    // Verify R3 = R1 + R2 = 30
    TEST_ASSERT_EQUAL_INT(30, r3_value);

    // Verify R4 = R2 - R1 = 10
    TEST_ASSERT_EQUAL_INT(10, r4_value);

    // Verify R5 = R3 * R4 = 30 * 10 = 300
    TEST_ASSERT_EQUAL_INT(300, r5_value);

    // Clean up
    remove_test_program();
    free(pipeline);
}
