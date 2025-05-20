#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../test_framework.h"
#include "../../libs/util/path.h"

// Test path joining operations
void test_path_join()
{
    printf("Running path joining tests...\n");

    // Test basic path joining
    const char *paths1[] = {"folder", "subfolder", "file.txt"};
    char result1[256] = {0};

    join_paths(result1, 3, paths1);

#ifdef _WIN32
    ASSERT_STR_EQUALS("folder\\subfolder\\file.txt", result1, "Basic path joining on Windows");
#else
    ASSERT_STR_EQUALS("folder/subfolder/file.txt", result1, "Basic path joining on Unix");
#endif

    // Test joining with already-terminated paths
    const char *paths2[] = {"folder/", "subfolder/", "file.txt"};
    char result2[256] = {0};

    join_paths(result2, 3, paths2);

#ifdef _WIN32
    ASSERT_STR_EQUALS("folder/\\subfolder/\\file.txt", result2, "Path joining with terminators on Windows");
#else
    ASSERT_STR_EQUALS("folder//subfolder//file.txt", result2, "Path joining with terminators on Unix");
#endif

    // Test joining with an empty path
    const char *paths3[] = {"folder", "", "file.txt"};
    char result3[256] = {0};

    join_paths(result3, 3, paths3);

#ifdef _WIN32
    ASSERT_STR_EQUALS("folder\\\\file.txt", result3, "Path joining with empty component on Windows");
#else
    ASSERT_STR_EQUALS("folder//file.txt", result3, "Path joining with empty component on Unix");
#endif

    // Test joining with a single path
    const char *paths4[] = {"single_file.txt"};
    char result4[256] = {0};

    join_paths(result4, 1, paths4);

    ASSERT_STR_EQUALS("single_file.txt", result4, "Path joining with single component");
}

// Test getting the last file from a path
void test_get_last_file_in_path()
{
    printf("Running get_last_file_in_path tests...\n");

    // Test basic Unix-style path
    const char *path1 = "/folder/subfolder/file.txt";
    const char *expected1 = "file.txt";
    const char *result1 = get_last_file_in_path(path1);

    ASSERT_STR_EQUALS(expected1, result1, "Getting last file from Unix-style path");

    // Test basic Windows-style path
    const char *path2 = "C:\\folder\\subfolder\\file.txt";
    const char *expected2 = "file.txt";
    const char *result2 = get_last_file_in_path(path2);

    ASSERT_STR_EQUALS(expected2, result2, "Getting last file from Windows-style path");

    // Test path with no separators
    const char *path3 = "file.txt";
    const char *expected3 = "file.txt";
    const char *result3 = get_last_file_in_path(path3);

    ASSERT_STR_EQUALS(expected3, result3, "Getting last file from path with no separators");

    // Test path ending with separator
    const char *path4 = "/folder/subfolder/";
    const char *expected4 = "";
    const char *result4 = get_last_file_in_path(path4);

    ASSERT_STR_EQUALS(expected4, result4, "Getting last file from path ending with separator");

    // Test mixed separators
    const char *path5 = "C:/folder\\subfolder/file.txt";
    const char *expected5 = "file.txt";
    const char *result5 = get_last_file_in_path(path5);

    ASSERT_STR_EQUALS(expected5, result5, "Getting last file from path with mixed separators");
}

int main()
{
    test_init();

    // Run tests
    test_path_join();
    test_get_last_file_in_path();

    // Print test summary
    test_summary();

    return (test_stats.failed == 0) ? TEST_SUCCESS : TEST_FAILURE;
}
