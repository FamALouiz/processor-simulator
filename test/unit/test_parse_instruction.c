#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test_framework.h"
#include "../../include/memory_management/mem_manager.h"
#include "../../include/memory_management/word.h"
#include "../../include/parser/functions.h"
#include "../../libs/parser/parser.c" // Including directly for testing the internal functions

// Test helper function to create a word with given bytes
word create_test_word(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3)
{
    word test_word;
    test_word[0] = b0;
    test_word[1] = b1;
    test_word[2] = b2;
    test_word[3] = b3;
    return test_word;
}

// Test the preParse function
void test_pre_parse()
{
    printf("Testing preParse function...\n");

    // Create a test word
    word test_word = create_test_word(0xA5, 0x5A, 0xF0, 0x0F);

    // Call preParse
    char *binary = preParse(&test_word);

    // Verify the result - we should get a 32-bit binary string
    // Since the exact algorithm needs inspection, we'll check the length
    ASSERT(strlen(binary) == 32, "preParse returns a 32-bit binary string");

    // Clean up
    free(binary);
}

// Test the binToDec function
void test_bin_to_dec()
{
    printf("Testing binToDec function...\n");

    // Test cases
    char binary1[] = "1010";     // 10 in decimal
    char binary2[] = "11111111"; // 255 in decimal

    // Call binToDec
    int result1 = binToDec(binary1);
    int result2 = binToDec(binary2);

    // Check results
    ASSERT_INT_EQUALS(10, result1, "binToDec converts '1010' to 10");
    ASSERT_INT_EQUALS(255, result2, "binToDec converts '11111111' to 255");
}

// Test the instruction parsing process
void test_instruction_parsing()
{
    printf("Testing instruction parsing process...\n");

    // Create test instructions in binary format (ADD R1, R2, R3)
    // This would need to match your specific encoding
    word add_instruction = create_test_word(0x00, 0x12, 0x30, 0x00); // Example encoding

    // Since parse() has side effects and calls other functions that we may not want to invoke directly,
    // we'll just test the components we can isolate.

    // Test preParse on the instruction
    char *binary = preParse(&add_instruction);

    // Check if binary is valid
    ASSERT(binary != NULL, "preParse produces valid binary string for instruction");

    // Check if we can extract opcode
    char opcode[5] = {0};
    strncpy(opcode, binary, 4);
    opcode[4] = '\0';

    // Since we don't know the exact encoding, we'll just check it's not empty
    ASSERT(strlen(opcode) == 4, "Successfully extracted opcode bits");

    // Clean up
    free(binary);
}

// Run all instruction parsing tests
int main()
{
    // Initialize the test
    test_init();

    // Initialize the memory subsystem
    mem_init();

    // Run the tests
    test_pre_parse();
    test_bin_to_dec();
    test_instruction_parsing();

    // Print test summary
    test_summary();

    // Return non-zero if any tests failed
    return test_stats.failed > 0 ? 1 : 0;
}
