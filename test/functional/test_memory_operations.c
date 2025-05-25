#include "unity.h"
#include "datapath.h"
#include "file_parser.h"
#include "mem_manager.h"
#include "word.h"
#include "config_loader.h"
#include <stdio.h>

// Test assembly file path
#define TEST_MEM_PROGRAM_PATH "functional_test_memory_program.asm"
#define CONFIG_FILE_PATH "InstructionMappings.config"

void init_config(void)
{
    FILE *file = fopen(CONFIG_FILE_PATH, "w");
    if (file == NULL)
    {
        perror("Failed to open config file for writing");
        return;
    }

    // Write valid configuration data
    fprintf(file, "ADD=0000# This is an inline comment\n");
    fprintf(file, "# This is a line comment\n");
    fprintf(file, "SUB=0001\n");
    fprintf(file, "MUL=0010\n");
    fprintf(file, "MOVI=0011\n");
    fprintf(file, "JEQ=0100\n");
    fprintf(file, "AND=0101\n");
    fprintf(file, "XORI=0110\n");
    fprintf(file, "JMP=0111\n");
    fprintf(file, "LSL=1000\n");
    fprintf(file, "LSR=1001\n");
    fprintf(file, "MOVR=1010\n");
    fprintf(file, "MOVM=1011\n\n\n");

    fclose(file);
}

void setUp(void)
{
    // Initialize configuration
    init_config();

    // Load configuration
    load_properties(CONFIG_FILE_PATH);

    // Initialize memory state
    memset(&main_memory, 0, sizeof(memory_interface));

    // Initialize program counter to 0
    initProgramCounter(0);
}

void tearDown(void)
{
}

void write_test_memory_program(void)
{
    // Create a test program that tests memory operations
    FILE *file = fopen(TEST_MEM_PROGRAM_PATH, "w");

    if (file == NULL)
    {
        TEST_FAIL_MESSAGE("Failed to create test memory program file");
    }

    // Write a program that:
    // 1. Sets R1 to 42 (MOVI)
    // 2. Sets R2 to memory address 1024 (DATA_INDEX) (MOVI)
    // 3. Stores R1 to memory at address in R2 (MOVM)
    // 4. Loads from memory at address in R2 to R3 (MOVR)
    fprintf(file, "# Memory operations test program\n");
    fprintf(file, "MOVI R1 42\n");
    fprintf(file, "MOVI R2 1024\n"); // DATA_INDEX
    fprintf(file, "MOVM R1 R2 0\n"); // Store R1 at address in R2 + 0
    fprintf(file, "MOVR R3 R2 0\n"); // Load from address in R2 + 0 to R3

    fclose(file);
}

void remove_test_memory_program(void)
{
    remove(TEST_MEM_PROGRAM_PATH);
}

void test_memory_operations(void)
{
    // Given a test program with memory operations
    write_test_memory_program();

    // When parsing and encoding the program
    parse_and_encode(TEST_MEM_PROGRAM_PATH);

    // And running the pipeline until completion
    pipeline_stage *pipeline = initializeStages();
    runPipeline(pipeline);

    // Then R1 should contain 42
    // And R3 should also contain 42 (loaded from memory)
    word r1_result, r3_result;
    unsigned int r1_value, r3_value;

    reg_read(R1, &r1_result);
    reg_read(R3, &r3_result);

    word_to_int(&r1_result, &r1_value);
    word_to_int(&r3_result, &r3_value);

    TEST_ASSERT_EQUAL_INT(42, r1_value);
    TEST_ASSERT_EQUAL_INT(42, r3_value);

    // Also verify the memory location directly
    word mem_content;
    unsigned int mem_value;

    mem_read(&mem_content, DATA_INDEX);
    word_to_int(&mem_content, &mem_value);

    TEST_ASSERT_EQUAL_INT(42, mem_value);

    // Clean up
    remove_test_memory_program();
    free(pipeline);
}

void write_test_memory_offset_program(void)
{
    // Create a test program that tests memory operations with offsets
    FILE *file = fopen(TEST_MEM_PROGRAM_PATH, "w");

    if (file == NULL)
    {
        TEST_FAIL_MESSAGE("Failed to create test memory program file");
    }

    // Write a program that:
    // 1. Sets R1 to 100 (MOVI)
    // 2. Sets R2 to 200 (MOVI)
    // 3. Sets R3 to memory address 1024 (DATA_INDEX) (MOVI)
    // 4. Stores R1 to memory at address in R3 + 4 (MOVM)
    // 5. Stores R2 to memory at address in R3 + 8 (MOVM)
    // 6. Loads from memory at address in R3 + 4 to R4 (MOVR)
    // 7. Loads from memory at address in R3 + 8 to R5 (MOVR)
    fprintf(file, "# Memory operations with offset test program\n");
    fprintf(file, "MOVI R1 100\n");
    fprintf(file, "MOVI R2 200\n");
    fprintf(file, "MOVI R3 1024\n"); // DATA_INDEX
    fprintf(file, "MOVM R1 R3 4\n"); // Store R1 at address in R3 + 4
    fprintf(file, "MOVM R2 R3 8\n"); // Store R2 at address in R3 + 8
    fprintf(file, "MOVR R4 R3 4\n"); // Load from address in R3 + 4 to R4
    fprintf(file, "MOVR R5 R3 8\n"); // Load from address in R3 + 8 to R5

    fclose(file);
}

void test_memory_operations_with_offset(void)
{
    // Given a test program with memory operations using offsets
    write_test_memory_offset_program();

    // When parsing and encoding the program
    parse_and_encode(TEST_MEM_PROGRAM_PATH);

    // And running the pipeline until completion
    pipeline_stage *pipeline = initializeStages();
    runPipeline(pipeline);

    // Then R4 should contain 100 (loaded from memory at offset 4)
    // And R5 should contain 200 (loaded from memory at offset 8)
    word r4_result, r5_result;
    unsigned int r4_value, r5_value;

    reg_read(R4, &r4_result);
    reg_read(R5, &r5_result);

    word_to_int(&r4_result, &r4_value);
    word_to_int(&r5_result, &r5_value);

    TEST_ASSERT_EQUAL_INT(100, r4_value);
    TEST_ASSERT_EQUAL_INT(200, r5_value);

    // Also verify the memory locations directly
    word mem_content1, mem_content2;
    unsigned int mem_value1, mem_value2;

    mem_read(&mem_content1, DATA_INDEX + 4);
    mem_read(&mem_content2, DATA_INDEX + 8);

    word_to_int(&mem_content1, &mem_value1);
    word_to_int(&mem_content2, &mem_value2);

    TEST_ASSERT_EQUAL_INT(100, mem_value1);
    TEST_ASSERT_EQUAL_INT(200, mem_value2);

    // Clean up
    remove_test_memory_program();
    free(pipeline);
}
