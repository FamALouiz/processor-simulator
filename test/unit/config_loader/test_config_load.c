#include "unity.h"
#include "config_loader.h"

#define CONFIG_FILE_PATH "test/data/valid_test_config.config"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_load_properties_should_load_valid_config(void)
{
    // Given a valid config file

    // When load_properties is called
    load_properties(CONFIG_FILE_PATH);

    char *add_opcode = NULL;
    Format add_type;
    get_config("ADD", &add_opcode, &add_type);

    char *sub_opcode = NULL;
    Format sub_type;
    get_config("SUB", &sub_opcode, &sub_type);

    const char *expected_add_opcode = "000";
    const int expected_add_type = 0;
    TEST_ASSERT_EQUAL_STRING(expected_add_opcode, add_opcode);
    TEST_ASSERT_EQUAL_INT(expected_add_type, add_type);

    const char *expected_sub_opcode = "001";
    const int expected_sub_type = 0;
    TEST_ASSERT_EQUAL_STRING(expected_sub_opcode, sub_opcode);
    TEST_ASSERT_EQUAL_INT(expected_sub_type, sub_type);
}
