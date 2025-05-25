#include "unity.h"
#include "config_loader.h"
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

#define CONFIG_FILE_PATH "valid_test_config.config"

void clear_config(void)
{
    remove(CONFIG_FILE_PATH);
}

void init_config(void)
{
    FILE *file = fopen(CONFIG_FILE_PATH, "w");
    if (file == NULL)
    {
        perror("Failed to open config file for writing");
        return;
    }

    // Write valid configuration data
    fprintf(file, "ADD=0000# This is an inline comment\n");
    fprintf(file, "# This is a line comment\n");
    fprintf(file, "SUB=0001\n");
    fprintf(file, "MUL=0010\n");
    fprintf(file, "MOVI=0011\n");
    fprintf(file, "JEQ=0100\n");
    fprintf(file, "AND=0101\n");
    fprintf(file, "XORI=0110\n");
    fprintf(file, "JMP=0111\n");
    fprintf(file, "LSL=1000\n");
    fprintf(file, "LSR=1001\n");
    fprintf(file, "MOVR=1010\n");
    fprintf(file, "MOVM=1011\n\n\n");

    fclose(file);
}

void setUp(void)
{
    init_config();
}

void tearDown(void)
{
    clear_config();
}

void test_load_properties_should_load_valid_config(void)
{
    // When load_properties is called
    load_properties(CONFIG_FILE_PATH);

    char *add_opcode = NULL;
    Format add_type;
    get_config("ADD", &add_opcode, &add_type);

    char *sub_opcode = NULL;
    Format sub_type;
    get_config("SUB", &sub_opcode, &sub_type);

    const char *expected_add_opcode = "0000";
    const int expected_add_type = 0;
    TEST_ASSERT_EQUAL_STRING(expected_add_opcode, add_opcode);
    TEST_ASSERT_EQUAL_INT(expected_add_type, add_type);

    const char *expected_sub_opcode = "0001";
    const int expected_sub_type = 0;
    TEST_ASSERT_EQUAL_STRING(expected_sub_opcode, sub_opcode);
    TEST_ASSERT_EQUAL_INT(expected_sub_type, sub_type);
}

void test_load_all_properties_correctly(void)
{
    // When load_properties is called
    load_properties(CONFIG_FILE_PATH);

    char *opcode = NULL;
    Format type;

    // Check all mnemonics
    get_config("ADD", &opcode, &type);
    TEST_ASSERT_EQUAL_STRING("0000", opcode);
    TEST_ASSERT_EQUAL_INT(R_TYPE, type);

    get_config("SUB", &opcode, &type);
    TEST_ASSERT_EQUAL_STRING("0001", opcode);
    TEST_ASSERT_EQUAL_INT(R_TYPE, type);

    get_config("MUL", &opcode, &type);
    TEST_ASSERT_EQUAL_STRING("0010", opcode);
    TEST_ASSERT_EQUAL_INT(R_TYPE, type);

    get_config("MOVI", &opcode, &type);
    TEST_ASSERT_EQUAL_STRING("0011", opcode);
    TEST_ASSERT_EQUAL_INT(I_TYPE, type);

    get_config("JEQ", &opcode, &type);
    TEST_ASSERT_EQUAL_STRING("0100", opcode);
    TEST_ASSERT_EQUAL_INT(I_TYPE, type);

    get_config("AND", &opcode, &type);
    TEST_ASSERT_EQUAL_STRING("0101", opcode);
    TEST_ASSERT_EQUAL_INT(R_TYPE, type);

    get_config("XORI", &opcode, &type);
    TEST_ASSERT_EQUAL_STRING("0110", opcode);
    TEST_ASSERT_EQUAL_INT(I_TYPE, type);

    get_config("JMP", &opcode, &type);
    TEST_ASSERT_EQUAL_STRING("0111", opcode);
    TEST_ASSERT_EQUAL_INT(J_TYPE, type);

    get_config("LSL", &opcode, &type);
    TEST_ASSERT_EQUAL_STRING("1000", opcode);
    TEST_ASSERT_EQUAL_INT(R_TYPE, type);

    get_config("LSR", &opcode, &type);
    TEST_ASSERT_EQUAL_STRING("1001", opcode);
    TEST_ASSERT_EQUAL_INT(R_TYPE, type);

    get_config("MOVR", &opcode, &type);
    TEST_ASSERT_EQUAL_STRING("1010", opcode);
    TEST_ASSERT_EQUAL_INT(I_TYPE, type);

    get_config("MOVM", &opcode, &type);
    TEST_ASSERT_EQUAL_STRING("1011", opcode);
    TEST_ASSERT_EQUAL_INT(I_TYPE, type);
}

void test_config_with_comments(void)
{
    // When load_properties is called
    load_properties(CONFIG_FILE_PATH);

    char *add_opcode = NULL;
    Format add_type;
    get_config("ADD", &add_opcode, &add_type);

    const char *expected_add_opcode = "0000";
    const int expected_add_type = R_TYPE;
    TEST_ASSERT_EQUAL_STRING(expected_add_opcode, add_opcode);
    TEST_ASSERT_EQUAL_INT(expected_add_type, add_type);
}

void test_config_with_empty_line(void)
{
    // Create a config file with an empty line
    FILE *file = fopen(CONFIG_FILE_PATH, "w");
    if (file == NULL)
    {
        perror("Failed to open config file for writing");
        return;
    }

    // Write valid configuration data with an empty line
    fprintf(file, "ADD=0000\n");
    fprintf(file, "\n"); // Empty line
    fprintf(file, "SUB=0001\n");

    fclose(file);

    // When load_properties is called
    load_properties(CONFIG_FILE_PATH);

    char *add_opcode = NULL;
    Format add_type;
    get_config("ADD", &add_opcode, &add_type);

    const char *expected_add_opcode = "0000";
    const int expected_add_type = R_TYPE;
    TEST_ASSERT_EQUAL_STRING(expected_add_opcode, add_opcode);
    TEST_ASSERT_EQUAL_INT(expected_add_type, add_type);

    char *sub_opcode = NULL;
    Format sub_type;
    get_config("SUB", &sub_opcode, &sub_type);

    const char *expected_sub_opcode = "0001";
    const int expected_sub_type = R_TYPE;
    TEST_ASSERT_EQUAL_STRING(expected_sub_opcode, sub_opcode);
    TEST_ASSERT_EQUAL_INT(expected_sub_type, sub_type);
}

void test_config_with_invalid_property(void)
{
    // When load_properties is called
    load_properties(CONFIG_FILE_PATH);

    char *opcode = NULL;
    Format type;

    // Check all mnemonics
    get_config("TEST", &opcode, &type);
    TEST_ASSERT_NULL(opcode);
    TEST_ASSERT_EQUAL_INT(-1, type);
}