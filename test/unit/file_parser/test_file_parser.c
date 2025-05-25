#include "unity.h"
#include "file_parser.h"
#include "mem_manager.h"
#include <stdio.h>

#define TEST_ASM_FILE "test/data/test_program.asm"

void setUp(void)
{
    memset(&main_memory, 0, sizeof(memory_interface));
}

void tearDown(void)
{
}

void write_test_asm_file(void)
{
    FILE *file = fopen(TEST_ASM_FILE, "w");
    if (file == NULL)
    {
        TEST_FAIL_MESSAGE("Failed to create test assembly file");
    }

    fprintf(file, "ADD R1 R2 R3\n");
    fprintf(file, "SUB R4 R5 R6\n");

    fclose(file);
}

void remove_test_asm_file(void)
{
    remove(TEST_ASM_FILE);
}

void test_parse_and_encode_simple_program(void)
{
    write_test_asm_file();

    parse_and_encode(TEST_ASM_FILE);

    remove_test_asm_file();

    TEST_PASS_MESSAGE("parse_and_encode completed without errors");
}

// If the file_parser.h exposes more functions, add tests for them here
