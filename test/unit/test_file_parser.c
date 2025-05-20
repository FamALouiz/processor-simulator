#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test_framework.h"
#include "../../include/file_parser/file_parser.h"
#include "../../include/config_loader/config_loader.h"
#include "../../include/memory_management/mem_manager.h"

// Create a test assembly file
void create_test_assembly_file(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Failed to create test assembly file\n");
        exit(1);
    }

    // Write some test assembly instructions
    fprintf(file, "ADD R1 R2 R3\n");
    fprintf(file, "SUB R4 R5 R6\n");
    fprintf(file, "MUL R7 R8 R9\n");
    fprintf(file, "# This is a comment\n");
    fprintf(file, "MOVI R10 42\n");
    fprintf(file, "JEQ R11 R12 10\n");
    fprintf(file, "\n"); // Empty line
    fprintf(file, "JMP 100\n");

    fclose(file);
}

// Test instruction format determination
void test_get_format()
{
    printf("Running instruction format tests...\n");

    // Test R-type instructions
    Format format = get_format("ADD");
    ASSERT_INT_EQUALS(R_TYPE, format, "ADD instruction format");

    format = get_format("SUB");
    ASSERT_INT_EQUALS(R_TYPE, format, "SUB instruction format");

    format = get_format("MUL");
    ASSERT_INT_EQUALS(R_TYPE, format, "MUL instruction format");

    format = get_format("AND");
    ASSERT_INT_EQUALS(R_TYPE, format, "AND instruction format");

    format = get_format("LSL");
    ASSERT_INT_EQUALS(R_TYPE, format, "LSL instruction format");

    format = get_format("LSR");
    ASSERT_INT_EQUALS(R_TYPE, format, "LSR instruction format");

    // Test I-type instructions
    format = get_format("MOVI");
    ASSERT_INT_EQUALS(I_TYPE, format, "MOVI instruction format");

    format = get_format("JEQ");
    ASSERT_INT_EQUALS(I_TYPE, format, "JEQ instruction format");

    format = get_format("XORI");
    ASSERT_INT_EQUALS(I_TYPE, format, "XORI instruction format");

    format = get_format("MOVR");
    ASSERT_INT_EQUALS(I_TYPE, format, "MOVR instruction format");

    format = get_format("MOVM");
    ASSERT_INT_EQUALS(I_TYPE, format, "MOVM instruction format");

    // Test J-type instructions
    format = get_format("JMP");
    ASSERT_INT_EQUALS(J_TYPE, format, "JMP instruction format");
}

// Test register index conversion
void test_get_register_index()
{
    printf("Running register index conversion tests...\n");

    // Test R0 (special case)
    int index = get_register_index("R0");
    ASSERT_INT_EQUALS(0, index, "R0 register index");

    // Test regular registers
    index = get_register_index("R1");
    ASSERT_INT_EQUALS(0, index, "R1 register index");

    index = get_register_index("R5");
    ASSERT_INT_EQUALS(4, index, "R5 register index");

    index = get_register_index("R10");
    ASSERT_INT_EQUALS(9, index, "R10 register index");

    index = get_register_index("R31");
    ASSERT_INT_EQUALS(30, index, "R31 register index");

    // Test invalid register
    index = get_register_index("X5");
    ASSERT_INT_EQUALS(-1, index, "Invalid register identifier");
}

// Test binary conversion
void test_to_binary()
{
    printf("Running binary conversion tests...\n");

    char bin[9]; // 8 bits + null terminator

    // Test conversion of 0
    to_binary(bin, 0, 8);
    ASSERT_STR_EQUALS("00000000", bin, "Convert 0 to 8-bit binary");

    // Test conversion of positive numbers
    to_binary(bin, 5, 8);
    ASSERT_STR_EQUALS("00000101", bin, "Convert 5 to 8-bit binary");

    to_binary(bin, 255, 8);
    ASSERT_STR_EQUALS("11111111", bin, "Convert 255 to 8-bit binary");

    // Test conversion with fewer bits
    to_binary(bin, 5, 4);
    ASSERT_STR_EQUALS("0101", bin, "Convert 5 to 4-bit binary");

    // Test conversion of larger numbers (truncation expected)
    to_binary(bin, 256, 8); // 256 = 100000000 in binary, 8 bits can only represent up to 255
    ASSERT_STR_EQUALS("00000000", bin, "Convert 256 to 8-bit binary (truncation)");
}

int main()
{
    test_init();

    // Run tests
    test_get_format();
    test_get_register_index();
    test_to_binary();

    // Print test summary
    test_summary();

    return (test_stats.failed == 0) ? TEST_SUCCESS : TEST_FAILURE;
}
