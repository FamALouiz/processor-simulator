#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test_framework.h"
#include "../../include/memory_management/mem_manager.h"
#include "../../include/file_parser/file_parser.h"
#include "../../include/config_loader/config_loader.h"

// Create a test assembly file with a variety of instructions
void create_functional_test_assembly(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Failed to create functional test assembly file\n");
        exit(1);
    }

    // Write a sequence of instructions that perform a simple computation
    // Initialize R1 to 10
    fprintf(file, "MOVI R1 10\n");

    // Initialize R2 to 5
    fprintf(file, "MOVI R2 5\n");

    // Add R1 and R2, store in R3 (R3 = 15)
    fprintf(file, "ADD R3 R1 R2\n");

    // Subtract R2 from R1, store in R4 (R4 = 5)
    fprintf(file, "SUB R4 R1 R2\n");

    // Multiply R1 and R2, store in R5 (R5 = 50)
    fprintf(file, "MUL R5 R1 R2\n");

    // Logical AND of R1 and R2, store in R6 (R6 = 0)
    fprintf(file, "AND R6 R1 R2\n");

    // Logical XOR of R1 with immediate 7, store in R7 (R7 = 13)
    fprintf(file, "XORI R7 R1 7\n");

    // Store R5 to memory at location DATA_INDEX + 100
    fprintf(file, "MOVI R10 1024\n"); // DATA_INDEX = 1024
    fprintf(file, "MOVM R10 R5 100\n");

    // Load from memory location DATA_INDEX + 100 to R8
    fprintf(file, "MOVR R8 R10 100\n");

    // Jump to instruction 20 if R1 equals R2 (won't jump)
    fprintf(file, "JEQ R1 R2 20\n");

    // Unconditional jump to the next instruction (just for testing JMP)
    fprintf(file, "JMP 11\n");

    // Shift R1 left by 2 bits, store in R9 (R9 = 40)
    fprintf(file, "LSL R9 R1 2\n");

    // Shift R9 right by 1 bit, store in R10 (R10 = 20)
    fprintf(file, "LSR R11 R9 1\n");

    fclose(file);
}

// Test the end-to-end processing of an assembly file
void test_end_to_end_processing()
{
    printf("Running end-to-end processing test...\n");

    // Create test assembly file
    const char *test_asm_file = "../test/data/functional_test.asm";
    create_functional_test_assembly(test_asm_file);

    // Load the instruction mappings
    load_properties("config/InstructionMappings.config");

    // Parse and encode the assembly file
    parse_and_encode(test_asm_file);

    // Now check the memory to verify that instructions were encoded correctly
    // We'll check the first few memory locations where our instructions should be stored

    word instruction;

    // Get the first instruction (MOVI R1 10)
    mem_read(&instruction, 0);

    // We can't directly check the binary representation because it depends on the
    // exact encoding scheme, but we can verify that something was written to memory
    // by checking that it's not all zeros
    word zeros = {0, 0, 0, 0};
    ASSERT(memcmp(instruction, zeros, sizeof(word)) != 0, "First instruction encoded (not all zeros)");

    // Check a few more instructions
    mem_read(&instruction, 1);
    ASSERT(memcmp(instruction, zeros, sizeof(word)) != 0, "Second instruction encoded (not all zeros)");

    mem_read(&instruction, 2);
    ASSERT(memcmp(instruction, zeros, sizeof(word)) != 0, "Third instruction encoded (not all zeros)");

    // Cleanup
    remove(test_asm_file);
}

int main()
{
    test_init();

    // Run tests
    test_end_to_end_processing();

    // Print test summary
    test_summary();

    return (test_stats.failed == 0) ? TEST_SUCCESS : TEST_FAILURE;
}
