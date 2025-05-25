#include "unity.h"
#include "config_loader.h"

extern void test_load_properties_should_load_valid_config(void);
extern void test_load_all_properties_correctly(void);
extern void test_config_with_comments(void);
extern void test_config_with_empty_line(void);
extern void test_config_with_invalid_property(void);

// Function declarations that will be called in main
void setUp(void);
void tearDown(void);

// Main function to run all tests
int main(void)
{
    UNITY_BEGIN();

    // Run all tests for config_loader
    RUN_TEST(test_load_properties_should_load_valid_config);
    RUN_TEST(test_load_all_properties_correctly);
    RUN_TEST(test_config_with_comments);
    RUN_TEST(test_config_with_empty_line);
    RUN_TEST(test_config_with_invalid_property);

    return UNITY_END();
}
