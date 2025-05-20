#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test_framework.h"
#include "../../include/memory_management/mem_manager.h"
#include "../../include/memory_management/word.h"

// Test memory read/write operations
void test_memory_operations()
{
    printf("Running memory operations tests...\n");

    // Test data
    word test_data = {0x12, 0x34, 0x56, 0x78};
    word read_data;

    // Test memory write/read at valid index
    mem_write(&test_data, 100);
    mem_read(&read_data, 100);

    // Compare the read data with the written data
    ASSERT_MEM_EQUALS(test_data, read_data, sizeof(word), "Memory read/write at valid index");

    // Test memory write/read at boundary (highest valid index)
    mem_write(&test_data, MEM_SIZE - 1);
    mem_read(&read_data, MEM_SIZE - 1);

    // Compare the read data with the written data
    ASSERT_MEM_EQUALS(test_data, read_data, sizeof(word), "Memory read/write at boundary");

    // Test invalid index (should be handled by the mem_read function)
    // We can't directly test the error message, but the function should not crash
    word invalid_read;
    mem_read(&invalid_read, MEM_SIZE + 10); // Should log an error but not crash

    // No assertion here since we just verify that the function handles invalid indices
    // without crashing
}

// Test register read/write operations
void test_register_operations()
{
    printf("Running register operations tests...\n");

    // Test data
    word test_data = {0xAA, 0xBB, 0xCC, 0xDD};
    word read_data;

    // Test register write/read for R1
    reg_write(R1, &test_data);
    reg_read(R1, &read_data);

    // Compare the read data with the written data
    ASSERT_MEM_EQUALS(test_data, read_data, sizeof(word), "Register R1 read/write");

    // Test register write/read for R31 (PC)
    reg_write(R31, &test_data);
    reg_read(R31, &read_data);

    // Compare the read data with the written data
    ASSERT_MEM_EQUALS(test_data, read_data, sizeof(word), "Register R31 (PC) read/write");

    // Test read-only register R0 (should always contain zeros)
    word zeros = {0, 0, 0, 0};
    reg_read(R0, &read_data);

    // R0 should always contain zeros
    ASSERT_MEM_EQUALS(zeros, read_data, sizeof(word), "Register R0 read (should be zeros)");

    // Try to write to R0 (should be ignored)
    reg_write(R0, &test_data);
    reg_read(R0, &read_data);

    // R0 should still contain zeros after write attempt
    ASSERT_MEM_EQUALS(zeros, read_data, sizeof(word), "Register R0 after write attempt (should still be zeros)");

    // Test invalid register (should be handled by the reg_read function)
    // We can't directly test the error message, but the function should not crash
    word invalid_read;
    reg_read(100, &invalid_read); // Should log an error but not crash

    // No assertion here since we just verify that the function handles invalid indices
    // without crashing
}

int main()
{
    test_init();

    // Run tests
    test_memory_operations();
    test_register_operations();

    // Print test summary
    test_summary();

    return (test_stats.failed == 0) ? TEST_SUCCESS : TEST_FAILURE;
}
