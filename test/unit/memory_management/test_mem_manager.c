#include "unity.h"
#include "mem_manager.h"

void setUp(void)
{
    memset(&main_memory, 0, sizeof(memory_interface));
}

void tearDown(void)
{
    release_interrupt();
}

void test_mem_read_and_write(void)
{
    word data = {0xAA, 0xBB, 0xCC, 0xDD};
    unsigned int index = 100;
    word result = {0};

    mem_write(&data, index);
    mem_read(&result, index);

    TEST_ASSERT_EQUAL_UINT8(0xAA, result[0]);
    TEST_ASSERT_EQUAL_UINT8(0xBB, result[1]);
    TEST_ASSERT_EQUAL_UINT8(0xCC, result[2]);
    TEST_ASSERT_EQUAL_UINT8(0xDD, result[3]);
}

void test_reg_read_and_write(void)
{
    word data = {0x12, 0x34, 0x56, 0x78};
    mem_register reg = R5;
    word result = {0};

    reg_write(reg, &data);
    reg_read(reg, &result);

    TEST_ASSERT_EQUAL_UINT8(0x12, result[0]);
    TEST_ASSERT_EQUAL_UINT8(0x34, result[1]);
    TEST_ASSERT_EQUAL_UINT8(0x56, result[2]);
    TEST_ASSERT_EQUAL_UINT8(0x78, result[3]);
}

void test_pipeline_read_and_write(void)
{
    word data = {0xA1, 0xB2, 0xC3, 0xD4};
    mem_register pipe_reg = RID;
    word result = {0};

    pipeline_write(pipe_reg, &data);
    pipeline_read(pipe_reg, &result);

    TEST_ASSERT_EQUAL_UINT8(0xA1, result[0]);
    TEST_ASSERT_EQUAL_UINT8(0xB2, result[1]);
    TEST_ASSERT_EQUAL_UINT8(0xC3, result[2]);
    TEST_ASSERT_EQUAL_UINT8(0xD4, result[3]);
}

void test_memory_boundaries(void)
{
    word data1 = {0x11, 0x22, 0x33, 0x44};
    word data2 = {0x55, 0x66, 0x77, 0x88};
    word result1 = {0};
    word result2 = {0};

    mem_write(&data1, 0);            // First location
    mem_write(&data2, MEM_SIZE - 1); // Last location

    mem_read(&result1, 0);
    mem_read(&result2, MEM_SIZE - 1);

    TEST_ASSERT_EQUAL_UINT8(0x11, result1[0]);
    TEST_ASSERT_EQUAL_UINT8(0x22, result1[1]);
    TEST_ASSERT_EQUAL_UINT8(0x33, result1[2]);
    TEST_ASSERT_EQUAL_UINT8(0x44, result1[3]);

    TEST_ASSERT_EQUAL_UINT8(0x55, result2[0]);
    TEST_ASSERT_EQUAL_UINT8(0x66, result2[1]);
    TEST_ASSERT_EQUAL_UINT8(0x77, result2[2]);
    TEST_ASSERT_EQUAL_UINT8(0x88, result2[3]);
}

void test_interrupt_functions(void)
{
    int initial_state = return_interrupt();
    TEST_ASSERT_EQUAL_INT(0, initial_state);

    set_interrupt();
    TEST_ASSERT_EQUAL_INT(1, return_interrupt());

    release_interrupt();
    TEST_ASSERT_EQUAL_INT(0, return_interrupt());
}
