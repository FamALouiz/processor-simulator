#include "unity.h"
#include "functions.h"
#include "mem_manager.h"
#include "word.h"

void setUp(void)
{
    memset(&main_memory, 0, sizeof(memory_interface));
}

void tearDown(void)
{
}

void test_add_function(void)
{
    word value1 = {0x00, 0x00, 0x00, 0x0A}; // Value 10
    word value2 = {0x00, 0x00, 0x00, 0x14}; // Value 20
    reg_write(R1, &value1);
    reg_write(R2, &value2);

    add(R3, R1, R2);

    word result = {0};
    reg_read(R3, &result);

    unsigned int result_int;
    word_to_int(&result, &result_int);

    TEST_ASSERT_EQUAL_INT(30, result_int);
}

void test_sub_function(void)
{
    word value1 = {0x00, 0x00, 0x00, 0x32}; // Value 50
    word value2 = {0x00, 0x00, 0x00, 0x19}; // Value 25
    reg_write(R4, &value1);
    reg_write(R5, &value2);

    sub(R6, R4, R5);

    word result = {0};
    reg_read(R6, &result);

    unsigned int result_int;
    word_to_int(&result, &result_int);

    TEST_ASSERT_EQUAL_INT(25, result_int);
}

void test_mul_function(void)
{
    word value1 = {0x00, 0x00, 0x00, 0x06}; // Value 6
    word value2 = {0x00, 0x00, 0x00, 0x07}; // Value 7
    reg_write(R7, &value1);
    reg_write(R8, &value2);

    mul(R9, R7, R8);

    word result = {0};
    reg_read(R9, &result);

    unsigned int result_int;
    word_to_int(&result, &result_int);

    TEST_ASSERT_EQUAL_INT(42, result_int);
}

void test_and_function(void)
{
    word value1 = {0x00, 0x00, 0x00, 0x0F}; // Value 15 (0000 1111)
    word value2 = {0x00, 0x00, 0x00, 0x33}; // Value 51 (0011 0011)
    reg_write(R10, &value1);
    reg_write(R11, &value2);

    and(R12, R10, R11);

    word result = {0};
    reg_read(R12, &result);

    unsigned int result_int;
    word_to_int(&result, &result_int);

    TEST_ASSERT_EQUAL_INT(3, result_int);
}

void test_movi_function(void)
{
    word imm_value = {0x00, 0x00, 0x00, 0x2A}; // Value 42

    movi(R13, &imm_value);

    word result = {0};
    reg_read(R13, &result);

    unsigned int result_int;
    word_to_int(&result, &result_int);

    TEST_ASSERT_EQUAL_INT(42, result_int);
}

void test_lsl_function(void)
{
    word value = {0x00, 0x00, 0x00, 0x05}; // Value 5
    reg_write(R14, &value);

    lsl(R15, R14, 2);

    word result = {0};
    reg_read(R15, &result);

    unsigned int result_int;
    word_to_int(&result, &result_int);

    TEST_ASSERT_EQUAL_INT(20, result_int);
}

void test_lsr_function(void)
{
    word value = {0x00, 0x00, 0x00, 0x14}; // Value 20
    reg_write(R16, &value);

    lsr(R17, R16, 2);

    word result = {0};
    reg_read(R17, &result);

    unsigned int result_int;
    word_to_int(&result, &result_int);

    TEST_ASSERT_EQUAL_INT(5, result_int);
}

void test_xori_function(void)
{
    word value = {0x00, 0x00, 0x00, 0x0F}; // Value 15 (0000 1111)
    int imm = 0x33;                        // Value 51 (0011 0011)
    reg_write(R18, &value);

    xori(R19, R18, imm);

    word result = {0};
    reg_read(R19, &result);

    unsigned int result_int;
    word_to_int(&result, &result_int);

    TEST_ASSERT_EQUAL_INT(60, result_int);
}
