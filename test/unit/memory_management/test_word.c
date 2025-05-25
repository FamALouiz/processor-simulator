#include "unity.h"
#include "word.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_int_to_word_conversion(void)
{
    // Given an integer value
    unsigned int input = 0x12345678;
    word output;

    // When converting to word
    int_to_word(input, &output);

    // Then the word should contain the correct byte representation
    TEST_ASSERT_EQUAL_UINT8(0x78, output[0]); // LSB
    TEST_ASSERT_EQUAL_UINT8(0x56, output[1]);
    TEST_ASSERT_EQUAL_UINT8(0x34, output[2]);
    TEST_ASSERT_EQUAL_UINT8(0x12, output[3]); // MSB
}

void test_word_to_int_conversion(void)
{
    // Given a word with known byte values
    word input = {0x78, 0x56, 0x34, 0x12};
    unsigned int output = 0;

    // When converting to int
    word_to_int(&input, &output);

    // Then the int should have the expected value
    TEST_ASSERT_EQUAL_UINT(0x12345678, output);
}

void test_round_trip_conversion(void)
{
    // Given an initial integer value
    unsigned int initial_int = 0xABCDEF01;
    unsigned int final_int = 0;
    word intermediate;

    // When converting int to word and back to int
    int_to_word(initial_int, &intermediate);
    word_to_int(&intermediate, &final_int);

    // Then the final int should equal the initial int
    TEST_ASSERT_EQUAL_UINT(initial_int, final_int);
}

void test_zero_value_conversion(void)
{
    // Given a zero integer value
    unsigned int input_int = 0;
    unsigned int output_int = 0;
    word intermediate;

    // When converting to word and back
    int_to_word(input_int, &intermediate);

    // Then all bytes in the word should be zero
    TEST_ASSERT_EQUAL_UINT8(0x00, intermediate[0]);
    TEST_ASSERT_EQUAL_UINT8(0x00, intermediate[1]);
    TEST_ASSERT_EQUAL_UINT8(0x00, intermediate[2]);
    TEST_ASSERT_EQUAL_UINT8(0x00, intermediate[3]);

    // And converting back should give zero
    word_to_int(&intermediate, &output_int);
    TEST_ASSERT_EQUAL_UINT(0, output_int);
}
