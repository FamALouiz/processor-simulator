#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test_framework.h"
#include "../../include/parser/functions.h"
#include "../../include/memory_management/mem_manager.h"
#include "../../include/memory_management/word.h"

// Test binary conversion function in parser
void test_bin_to_dec()
{
    printf("Running binary to decimal conversion tests...\n");

    // Unfortunately, the binToDec function is not exposed in a header file
    // For testing, we would need to either expose this function or re-implement it here
    // Since we can't easily test this function externally, we'll create a test stub

    // Test data - we'll manually verify these conversions
    // Binary "1010" should be 10 in decimal
    // Binary "1111" should be 15 in decimal
    // Binary "10000" should be 16 in decimal

    // For now, we'll just print a message
    printf("Note: Binary to decimal conversion tests would need the function to be exposed in a header\n");

    // In an actual implementation, you would call binToDec and assert on the results:
    // ASSERT_INT_EQUALS(10, binToDec("1010"), "Binary '1010' to decimal conversion");
    // ASSERT_INT_EQUALS(15, binToDec("1111"), "Binary '1111' to decimal conversion");
    // ASSERT_INT_EQUALS(16, binToDec("10000"), "Binary '10000' to decimal conversion");
}

// Test basic arithmetic operations
void test_arithmetic_operations()
{
    printf("Running arithmetic operation tests...\n");

    // Test ADD operation
    word reg0_value = {0x00, 0x00, 0x00, 0x05};   // Value 5
    word reg1_value = {0x00, 0x00, 0x00, 0x03};   // Value 3
    word expected_sum = {0x00, 0x00, 0x00, 0x08}; // Expected sum: 8
    word result;

    // Set up test registers
    reg_write(R1, &reg0_value);
    reg_write(R2, &reg1_value);

    // Perform ADD operation
    add(R3, R1, R2);

    // Read result
    reg_read(R3, &result);

    // Assert the result
    ASSERT_MEM_EQUALS(expected_sum, result, sizeof(word), "ADD operation");

    // Test SUB operation
    word expected_diff = {0x00, 0x00, 0x00, 0x02}; // Expected difference: 2

    // Perform SUB operation
    sub(R4, R1, R2);

    // Read result
    reg_read(R4, &result);

    // Assert the result
    ASSERT_MEM_EQUALS(expected_diff, result, sizeof(word), "SUB operation");

    // Test MUL operation
    word expected_product = {0x00, 0x00, 0x00, 0x0F}; // Expected product: 15

    // Perform MUL operation
    mul(R5, R1, R2);

    // Read result
    reg_read(R5, &result);

    // Assert the result
    ASSERT_MEM_EQUALS(expected_product, result, sizeof(word), "MUL operation");
}

// Test logical operations
void test_logical_operations()
{
    printf("Running logical operation tests...\n");

    // Test AND operation
    word reg0_value = {0x00, 0x00, 0x00, 0x05};   // Value 5 (binary 0101)
    word reg1_value = {0x00, 0x00, 0x00, 0x03};   // Value 3 (binary 0011)
    word expected_and = {0x00, 0x00, 0x00, 0x01}; // Expected AND: 1 (binary 0001)
    word result;

    // Set up test registers
    reg_write(R1, &reg0_value);
    reg_write(R2, &reg1_value);

    // Perform AND operation
    and(R3, R1, R2);

    // Read result
    reg_read(R3, &result);

    // Assert the result
    ASSERT_MEM_EQUALS(expected_and, result, sizeof(word), "AND operation");

    // Test XORI operation
    int imm_value = 0x0A;                         // Immediate value 10 (binary 1010)
    word expected_xor = {0x00, 0x00, 0x00, 0x0F}; // Expected XOR: 15 (binary 1111)

    // Perform XORI operation
    xori(R4, R1, imm_value);

    // Read result
    reg_read(R4, &result);

    // Assert the result
    ASSERT_MEM_EQUALS(expected_xor, result, sizeof(word), "XORI operation");
}

// Test shift operations
void test_shift_operations()
{
    printf("Running shift operation tests...\n");

    // Test LSL (logical shift left) operation
    word reg_value = {0x00, 0x00, 0x00, 0x05}; // Value 5 (binary 0101)
    int shift_amount = 2;
    word expected_lsl = {0x00, 0x00, 0x00, 0x14}; // Expected LSL by 2: 20 (binary 10100)
    word result;

    // Set up test register
    reg_write(R1, &reg_value);

    // Perform LSL operation
    lsl(R2, R1, shift_amount);

    // Read result
    reg_read(R2, &result);

    // Assert the result
    ASSERT_MEM_EQUALS(expected_lsl, result, sizeof(word), "LSL operation");

    // Test LSR (logical shift right) operation
    word reg_value2 = {0x00, 0x00, 0x00, 0x14};   // Value 20 (binary 10100)
    word expected_lsr = {0x00, 0x00, 0x00, 0x05}; // Expected LSR by 2: 5 (binary 0101)

    // Set up test register
    reg_write(R3, &reg_value2);

    // Perform LSR operation
    lsr(R4, R3, shift_amount);

    // Read result
    reg_read(R4, &result);

    // Assert the result
    ASSERT_MEM_EQUALS(expected_lsr, result, sizeof(word), "LSR operation");
}

// Test move operations
void test_move_operations()
{
    printf("Running move operation tests...\n");

    // Test MOVI (move immediate) operation
    word imm_value = {0x12, 0x34, 0x56, 0x78};
    word result;

    // Perform MOVI operation
    movi(R1, imm_value);

    // Read result
    reg_read(R1, &result);

    // Assert the result
    ASSERT_MEM_EQUALS(imm_value, result, sizeof(word), "MOVI operation");

    // Test MOVR (move from memory to register) operation
    word mem_value = {0xAA, 0xBB, 0xCC, 0xDD};
    int offset = 10;
    unsigned int mem_addr = DATA_INDEX + offset;

    // Set up memory value
    mem_write(&mem_value, mem_addr);

    // Set up address register
    word addr_reg_value = {0x00, 0x00, 0x00, DATA_INDEX};
    reg_write(R2, &addr_reg_value);

    // Perform MOVR operation
    movr(R3, R2, offset);

    // Read result
    reg_read(R3, &result);

    // Assert the result
    ASSERT_MEM_EQUALS(mem_value, result, sizeof(word), "MOVR operation");

    // Test MOVM (move from register to memory) operation
    word reg_value = {0x11, 0x22, 0x33, 0x44};
    word mem_read_value;
    int offset2 = 20;
    unsigned int mem_addr2 = DATA_INDEX + offset2;

    // Set up register value
    reg_write(R4, &reg_value);

    // Perform MOVM operation
    movm(R2, R4, offset2);

    // Read memory value
    mem_read(&mem_read_value, mem_addr2);

    // Assert the result
    ASSERT_MEM_EQUALS(reg_value, mem_read_value, sizeof(word), "MOVM operation");
}

int main()
{
    test_init();

    // Run tests
    test_bin_to_dec();
    test_arithmetic_operations();
    test_logical_operations();
    test_shift_operations();
    test_move_operations();

    // Print test summary
    test_summary();

    return (test_stats.failed == 0) ? TEST_SUCCESS : TEST_FAILURE;
}
