#include "unity.h"
#include "config_loader.h"

extern void test_load_properties_should_load_valid_config(void);

// Function declarations that will be called in main
void setUp(void);
void tearDown(void);

// Main function to run all tests
int main(void)
{
    UNITY_BEGIN();

    // Run all tests for config_loader
    RUN_TEST(test_load_properties_should_load_valid_config);

    return UNITY_END();
}
