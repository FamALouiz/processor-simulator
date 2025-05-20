#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test_framework.h"
#include "../../include/config_loader/config_loader.h"
#include "../../include/file_parser/file_parser.h"

// Create a test config file
void create_test_config_file(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Failed to create test config file\n");
        exit(1);
    }

    // Write some test instruction mappings
    fprintf(file, "TEST1=0000\n");
    fprintf(file, "TEST2=0001\n");
    fprintf(file, "TEST3=0010\n");
    fprintf(file, "# This is a comment\n");
    fprintf(file, "TEST4=0011 # Inline comment\n");
    fprintf(file, "TEST5=0100\n");
    fprintf(file, "\n"); // Empty line
    fprintf(file, "TEST6=0101\n");

    fclose(file);
}

// Test config loading
void test_config_loading()
{
    printf("Running config loading tests...\n");

    // Create a test config file
    const char *test_config_file = "../test/data/test_instruction_mappings.config";
    create_test_config_file(test_config_file);

    // Load the config file
    load_properties(test_config_file);

    // Test retrieving config for various mnemonics
    char *bin_opcode;
    Format type;

    // Test valid mnemonics
    // Note: The get_config function modifies the bin_opcode pointer, so we need to check
    // the return value rather than the pointer itself
    get_config("TEST1", &bin_opcode, &type);
    if (bin_opcode != NULL)
    {
        ASSERT_STR_EQUALS("0000", bin_opcode, "Config retrieval for TEST1");
    }
    else
    {
        ASSERT(false, "Config retrieval for TEST1 returned NULL");
    }

    get_config("TEST5", &bin_opcode, &type);
    if (bin_opcode != NULL)
    {
        ASSERT_STR_EQUALS("0100", bin_opcode, "Config retrieval for TEST5");
    }
    else
    {
        ASSERT(false, "Config retrieval for TEST5 returned NULL");
    }

    // Test invalid mnemonic (should set bin_opcode to NULL)
    get_config("NON_EXISTENT", &bin_opcode, &type);
    ASSERT(bin_opcode == NULL, "Config retrieval for non-existent mnemonic");
    ASSERT(type == -1, "Format for non-existent mnemonic");

    // Cleanup
    remove(test_config_file);
}

int main()
{
    test_init();

    // Run tests
    test_config_loading();

    // Print test summary
    test_summary();

    return (test_stats.failed == 0) ? TEST_SUCCESS : TEST_FAILURE;
}
