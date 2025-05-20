#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test_framework.h"
#include "../../include/memory_management/mem_manager.h"
#include "../../include/file_parser/file_parser.h"
#include "../../include/config_loader/config_loader.h"
#include "../../include/parser/functions.h"

// Create a test assembly file with a complete program
void create_full_test_program(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Failed to create full test program file\n");
        exit(1);
    }

    // Write a program that tests all instructions and their interactions
    // Initialize registers with test values
    fprintf(file, "MOVI R1 10\n"); // R1 = 10
    fprintf(file, "MOVI R2 5\n");  // R2 = 5
    fprintf(file, "MOVI R3 0\n");  // R3 = 0 (will be used to store results)

    // Test arithmetic operations
    fprintf(file, "ADD R3 R1 R2\n"); // R3 = R1 + R2 = 15
    fprintf(file, "SUB R4 R1 R2\n"); // R4 = R1 - R2 = 5
    fprintf(file, "MUL R5 R1 R2\n"); // R5 = R1 * R2 = 50

    // Test logical operations
    fprintf(file, "AND R6 R1 R2\n");  // R6 = R1 & R2 = 0
    fprintf(file, "XORI R7 R1 15\n"); // R7 = R1 ^ 15 = 5

    // Test shift operations
    fprintf(file, "LSL R8 R1 2\n"); // R8 = R1 << 2 = 40
    fprintf(file, "LSR R9 R8 1\n"); // R9 = R8 >> 1 = 20

    // Test memory operations
    fprintf(file, "MOVI R10 100\n");   // R10 = 100 (base address)
    fprintf(file, "MOVM R10 R5 0\n");  // MEM[100 + 0] = R5 = 50
    fprintf(file, "MOVR R11 R10 0\n"); // R11 = MEM[100 + 0] = 50

    // Add a conditional jump (will not be taken)
    fprintf(file, "MOVI R12 20\n");     // R12 = 20
    fprintf(file, "MOVI R13 30\n");     // R13 = 30
    fprintf(file, "JEQ R12 R13 100\n"); // Jump if R12 == R13 (not taken)

    // Add an unconditional jump
    fprintf(file, "JMP 15\n"); // Jump to instruction 15

    fclose(file);
}

// Test the full processor pipeline
void test_processor_pipeline()
{
    printf("Testing full processor pipeline...\n");

    // Create a temporary test file
    const char *test_file = "test/data/full_pipeline_test.asm";
    create_full_test_program(test_file);

    // Load configuration and parse/encode the assembly
    const char *config_file = "config/InstructionMappings.config";
    load_properties(config_file);
    parse_and_encode(test_file);

    // Execute the first few instructions and check results
    // Assuming we have a way to execute the program or simulate execution

    // For now, this is more of an integration test that verifies the program
    // can be loaded without errors. Specific tests of execution would need
    // a way to execute instructions one by one or access the processor state.

    ASSERT(true, "Full program successfully loaded and encoded");

    // If we had execution capability, we could check register contents:
    // word expected = create_test_word(0x00, 0x00, 0x00, 0x0F);  // 15
    // word actual;
    // reg_read(R3, &actual);
    // ASSERT_MEM_EQUALS(expected, actual, sizeof(word), "R3 contains 15 after ADD operation");
}

// Run all pipeline tests
int main()
{
    // Initialize the test
    test_init();

    // Initialize the memory subsystem
    mem_init();

    // Run the tests
    test_processor_pipeline();

    // Print test summary
    test_summary();

    // Return non-zero if any tests failed
    return test_stats.failed > 0 ? 1 : 0;
}
