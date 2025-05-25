#include "unity.h"
#include "word_parser.h"
#include "mem_manager.h"
#include "config_loader.h"

void setUp(void)
{
    load_properties("config/InstructionMappings.config");
    memset(&main_memory, 0, sizeof(memory_interface));
}

void tearDown(void)
{
}

void test_parse_add_instruction(void)
{
    word instruction = {0};
    unsigned int encoded_add = 0x00000000;
    char *add_opcode = NULL;
    Format add_type;

    get_config("ADD", &add_opcode, &add_type);
    int opcode_value = (int)strtol(add_opcode, NULL, 2);

    encoded_add = (opcode_value << 28) | (R1 << 23) | (R2 << 18) | (R3 << 13);
    int_to_word(encoded_add, &instruction);

    word r2_value = {0x00, 0x00, 0x00, 0x05}; // Value 5
    word r3_value = {0x00, 0x00, 0x00, 0x03}; // Value 3
    reg_write(R2, &r2_value);
    reg_write(R3, &r3_value);

    int result = parse(&instruction);

    word r1_result = {0};
    reg_read(R1, &r1_result);

    unsigned int r1_value_int;
    word_to_int(&r1_result, &r1_value_int);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(8, r1_value_int);
}

void test_parse_sub_instruction(void)
{
    word instruction = {0};
    unsigned int encoded_sub = 0x00000000;
    char *sub_opcode = NULL;
    Format sub_type;

    get_config("SUB", &sub_opcode, &sub_type);
    int opcode_value = (int)strtol(sub_opcode, NULL, 2);

    encoded_sub = (opcode_value << 28) | (R4 << 23) | (R5 << 18) | (R6 << 13);
    int_to_word(encoded_sub, &instruction);

    word r5_value = {0x00, 0x00, 0x00, 0x0A}; // Value 10
    word r6_value = {0x00, 0x00, 0x00, 0x04}; // Value 4
    reg_write(R5, &r5_value);
    reg_write(R6, &r6_value);

    int result = parse(&instruction);

    word r4_result = {0};
    reg_read(R4, &r4_result);

    unsigned int r4_value_int;
    word_to_int(&r4_result, &r4_value_int);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(6, r4_value_int);
}

void test_parse_end_instruction(void)
{
    word instruction = {0};
    unsigned int encoded_end = 0xF0000000; // END opcode is 0xF
    int_to_word(encoded_end, &instruction);

    int result = parse(&instruction);

    TEST_ASSERT_EQUAL_INT(1, result);
}
