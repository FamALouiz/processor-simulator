#include "unity.h"
#include "datapath.h"
#include "file_parser.h"
#include "mem_manager.h"
#include "word.h"
#include "config_loader.h"
#include <stdio.h>

#define TEST_BRANCH_PROGRAM_PATH "test/data/functional_test_branch_program.asm"

void setUp(void)
{
    // Load configuration
    load_properties("config/InstructionMappings.config");

    // Initialize memory state
    memset(&main_memory, 0, sizeof(memory_interface));

    // Initialize program counter to 0
    initProgramCounter(0);
}

void tearDown(void)
{
}

void write_test_branch_program(void)
{
    // Create a test program that tests branching and jumping
    FILE *file = fopen(TEST_BRANCH_PROGRAM_PATH, "w");

    if (file == NULL)
    {
        TEST_FAIL_MESSAGE("Failed to create test branch program file");
    }

    // Write a program that:
    // 1. Sets R1 to 5 (MOVI)
    // 2. Sets R2 to 5 (MOVI)
    // 3. Compare R1 and R2, if equal jump to EQUAL label (JEQ)
    // 4. If not equal, set R3 to 0 (MOVI)
    // 5. Jump to END (JMP)
    // 6. EQUAL: Set R3 to 1 (MOVI)
    // 7. END: No operation
    fprintf(file, "# Branch test program\n");
    fprintf(file, "MOVI R1, 5\n");
    fprintf(file, "MOVI R2, 5\n");
    fprintf(file, "JEQ R1, R2, EQUAL\n");
    fprintf(file, "MOVI R3, 0\n");
    fprintf(file, "JMP END\n");
    fprintf(file, "EQUAL: MOVI R3, 1\n");
    fprintf(file, "END: # End of program\n");

    fclose(file);
}

void remove_test_branch_program(void)
{
    remove(TEST_BRANCH_PROGRAM_PATH);
}

void test_branching_instructions(void)
{
    // Given a test program with branches
    write_test_branch_program();

    // When parsing and encoding the program
    parse_and_encode(TEST_BRANCH_PROGRAM_PATH);

    // And running the pipeline until completion
    pipeline_stage *pipeline = initializeStages();
    runPipeline(pipeline);

    // Then R3 should contain 1 (equal branch was taken)
    word r3_result;
    unsigned int r3_value;

    reg_read(R3, &r3_result);
    word_to_int(&r3_result, &r3_value);

    TEST_ASSERT_EQUAL_INT(1, r3_value);

    // Clean up
    remove_test_branch_program();
    free(pipeline);
}

void write_test_unequal_branch_program(void)
{
    // Create a test program that tests branching with unequal values
    FILE *file = fopen(TEST_BRANCH_PROGRAM_PATH, "w");

    if (file == NULL)
    {
        TEST_FAIL_MESSAGE("Failed to create test branch program file");
    }

    // Write a program that:
    // 1. Sets R1 to 5 (MOVI)
    // 2. Sets R2 to 10 (MOVI) - Different from R1
    // 3. Compare R1 and R2, if equal jump to EQUAL label (JEQ)
    // 4. If not equal, set R3 to 0 (MOVI)
    // 5. Jump to END (JMP)
    // 6. EQUAL: Set R3 to 1 (MOVI)
    // 7. END: No operation
    fprintf(file, "# Branch test program with unequal values\n");
    fprintf(file, "MOVI R1, 5\n");
    fprintf(file, "MOVI R2, 10\n");
    fprintf(file, "JEQ R1, R2, EQUAL\n");
    fprintf(file, "MOVI R3, 0\n");
    fprintf(file, "JMP END\n");
    fprintf(file, "EQUAL: MOVI R3, 1\n");
    fprintf(file, "END: # End of program\n");

    fclose(file);
}

void test_not_taken_branch(void)
{
    // Given a test program with branches that should not be taken
    write_test_unequal_branch_program();

    // When parsing and encoding the program
    parse_and_encode(TEST_BRANCH_PROGRAM_PATH);

    // And running the pipeline until completion
    pipeline_stage *pipeline = initializeStages();
    runPipeline(pipeline);

    // Then R3 should contain 0 (equal branch was not taken)
    word r3_result;
    unsigned int r3_value;

    reg_read(R3, &r3_result);
    word_to_int(&r3_result, &r3_value);

    TEST_ASSERT_EQUAL_INT(0, r3_value);

    // Clean up
    remove_test_branch_program();
    free(pipeline);
}
