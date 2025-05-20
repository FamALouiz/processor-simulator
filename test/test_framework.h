#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Colors for console output
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Test statistics
typedef struct
{
    int total;
    int passed;
    int failed;
} TestStats;

// Global statistics
static TestStats test_stats = {0, 0, 0};

// Initialize the test module
void test_init()
{
    test_stats.total = 0;
    test_stats.passed = 0;
    test_stats.failed = 0;
    printf(ANSI_COLOR_BLUE "========== RUNNING TESTS ==========\n" ANSI_COLOR_RESET);
}

// Print test results
void test_summary()
{
    printf(ANSI_COLOR_BLUE "\n========== TEST SUMMARY ==========\n" ANSI_COLOR_RESET);
    printf("Total tests: %d\n", test_stats.total);
    printf(ANSI_COLOR_GREEN "Passed: %d\n" ANSI_COLOR_RESET, test_stats.passed);
    printf(ANSI_COLOR_RED "Failed: %d\n" ANSI_COLOR_RESET, test_stats.failed);

    if (test_stats.failed == 0)
    {
        printf(ANSI_COLOR_GREEN "\nALL TESTS PASSED!\n" ANSI_COLOR_RESET);
    }
    else
    {
        printf(ANSI_COLOR_RED "\nSOME TESTS FAILED!\n" ANSI_COLOR_RESET);
    }
}

// Assert function for testing
#define ASSERT(condition, message)                                                                                \
    do                                                                                                            \
    {                                                                                                             \
        test_stats.total++;                                                                                       \
        if (condition)                                                                                            \
        {                                                                                                         \
            test_stats.passed++;                                                                                  \
            printf(ANSI_COLOR_GREEN "PASS" ANSI_COLOR_RESET ": %s\n", message);                                   \
        }                                                                                                         \
        else                                                                                                      \
        {                                                                                                         \
            test_stats.failed++;                                                                                  \
            printf(ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET ": %s (line %d in %s)\n", message, __LINE__, __FILE__); \
        }                                                                                                         \
    } while (0)

// Assert equals for integers
#define ASSERT_INT_EQUALS(expected, actual, message)                                                      \
    do                                                                                                    \
    {                                                                                                     \
        test_stats.total++;                                                                               \
        if ((expected) == (actual))                                                                       \
        {                                                                                                 \
            test_stats.passed++;                                                                          \
            printf(ANSI_COLOR_GREEN "PASS" ANSI_COLOR_RESET ": %s\n", message);                           \
        }                                                                                                 \
        else                                                                                              \
        {                                                                                                 \
            test_stats.failed++;                                                                          \
            printf(ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET ": %s (expected %d, got %d) (line %d in %s)\n", \
                   message, (expected), (actual), __LINE__, __FILE__);                                    \
        }                                                                                                 \
    } while (0)

// Assert equals for strings
#define ASSERT_STR_EQUALS(expected, actual, message)                                                          \
    do                                                                                                        \
    {                                                                                                         \
        test_stats.total++;                                                                                   \
        if (strcmp((expected), (actual)) == 0)                                                                \
        {                                                                                                     \
            test_stats.passed++;                                                                              \
            printf(ANSI_COLOR_GREEN "PASS" ANSI_COLOR_RESET ": %s\n", message);                               \
        }                                                                                                     \
        else                                                                                                  \
        {                                                                                                     \
            test_stats.failed++;                                                                              \
            printf(ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET ": %s (expected '%s', got '%s') (line %d in %s)\n", \
                   message, (expected), (actual), __LINE__, __FILE__);                                        \
        }                                                                                                     \
    } while (0)

// Assert memory equality
#define ASSERT_MEM_EQUALS(expected, actual, size, message)                                                     \
    do                                                                                                         \
    {                                                                                                          \
        test_stats.total++;                                                                                    \
        if (memcmp((expected), (actual), (size)) == 0)                                                         \
        {                                                                                                      \
            test_stats.passed++;                                                                               \
            printf(ANSI_COLOR_GREEN "PASS" ANSI_COLOR_RESET ": %s\n", message);                                \
        }                                                                                                      \
        else                                                                                                   \
        {                                                                                                      \
            test_stats.failed++;                                                                               \
            printf(ANSI_COLOR_RED "FAIL" ANSI_COLOR_RESET ": %s (memory comparison failed) (line %d in %s)\n", \
                   message, __LINE__, __FILE__);                                                               \
        }                                                                                                      \
    } while (0)

// Test result codes
#define TEST_SUCCESS 0
#define TEST_FAILURE 1

#endif // TEST_FRAMEWORK_H
