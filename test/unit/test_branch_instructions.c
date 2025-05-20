#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test_framework.h"
#include "../../include/memory_management/mem_manager.h"
#include "../../include/memory_management/word.h"
#include "../../include/parser/functions.h"

// Helper function to create a word with specific bytes
word create_test_word(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3)
{
    word test_word;
    test_word[0] = b0;
    test_word[1] = b1;
    test_word[2] = b2;
    test_word[3] = b3;
    return test_word;
}

// Global variables to help track program counter
extern int PC; // Assuming PC is defined elsewhere (likely in parser.c)

// Useful for checking the state of the PC without directly exposing it
int get_current_pc()
{
    return PC;
}

// Test the JEQ (Jump if Equal) instruction
void test_jeq_instruction()
{
    printf("Testing JEQ instruction...\n");

    // Test case 1: Equal registers, should jump
    // Setup test registers with equal values
    word equal_val = create_test_word(0x00, 0x00, 0x00, 0x0A); // 10 in decimal
    reg_write(R1, &equal_val);
    reg_write(R2, &equal_val);

    // Save the current PC value
    int start_pc = PC;
    int jump_offset = 100;

    // Execute JEQ instruction
    jeq(R1, R2, jump_offset);

    // Check if PC was incremented by jump offset
    ASSERT_INT_EQUALS(start_pc + jump_offset, PC, "JEQ with equal registers causes a jump");

    // Test case 2: Unequal registers, should not jump
    // Setup test registers with different values
    word val1 = create_test_word(0x00, 0x00, 0x00, 0x0A); // 10 in decimal
    word val2 = create_test_word(0x00, 0x00, 0x00, 0x14); // 20 in decimal
    reg_write(R1, &val1);
    reg_write(R2, &val2);

    // Reset PC for this test
    PC = start_pc;

    // Execute JEQ instruction
    jeq(R1, R2, jump_offset);

    // Check that PC was not changed (or was incremented normally)
    ASSERT_INT_EQUALS(start_pc, PC, "JEQ with unequal registers does not cause a jump");
}

// Test the JMP (Unconditional Jump) instruction
void test_jmp_instruction()
{
    printf("Testing JMP instruction...\n");

    // Save the current PC value
    int start_pc = PC;
    int jump_address = 200;

    // Execute JMP instruction
    jmp(jump_address);

    // Check if PC was set to the jump address
    ASSERT_INT_EQUALS(jump_address, PC, "JMP sets PC to the specified address");
}

// Run all branch instruction tests
int main()
{
    // Initialize the test
    test_init();

    // Initialize the memory subsystem
    mem_init();

    // Reset PC for testing
    PC = 0;

    // Run the tests
    test_jeq_instruction();
    test_jmp_instruction();

    // Print test summary
    test_summary();

    // Return non-zero if any tests failed
    return test_stats.failed > 0 ? 1 : 0;
}
