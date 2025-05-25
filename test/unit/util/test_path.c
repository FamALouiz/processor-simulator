#include "unity.h"
#include "path.h"
#include <string.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_join_paths(void)
{
    // Given path components
    const char *paths[] = {"folder1", "folder2", "file.txt"};
    char result[256] = {0};

    // When joining paths
    join_paths(result, 3, paths);

// Then the result should be the properly joined path
#ifdef _WIN32
    TEST_ASSERT_EQUAL_STRING("folder1\\folder2\\file.txt", result);
#else
    TEST_ASSERT_EQUAL_STRING("folder1/folder2/file.txt", result);
#endif
}

void test_join_paths_empty(void)
{
    // Given empty path components
    const char *paths[] = {"", "", ""};
    char result[256] = {0};

    // When joining paths
    join_paths(result, 3, paths);

// Then the result should handle empty components correctly
#ifdef _WIN32
    TEST_ASSERT_EQUAL_STRING("\\\\", result);
#else
    TEST_ASSERT_EQUAL_STRING("//", result);
#endif
}

void test_join_paths_single(void)
{
    // Given a single path component
    const char *paths[] = {"filename.txt"};
    char result[256] = {0};

    // When joining paths
    join_paths(result, 1, paths);

    // Then the result should be just the component
    TEST_ASSERT_EQUAL_STRING("filename.txt", result);
}

void test_get_last_file_in_path(void)
{
// Given a path with multiple components
#ifdef _WIN32
    const char *path = "c:\\folder1\\folder2\\file.txt";
#else
    const char *path = "/folder1/folder2/file.txt";
#endif

    // When getting the last file
    const char *last_file = get_last_file_in_path(path);

    // Then it should return the file name
    TEST_ASSERT_EQUAL_STRING("file.txt", last_file);
}

void test_get_last_file_in_path_no_separator(void)
{
    // Given a path with no separators
    const char *path = "file.txt";

    // When getting the last file
    const char *last_file = get_last_file_in_path(path);

    // Then it should return the input path
    TEST_ASSERT_EQUAL_STRING("file.txt", last_file);
}

void test_get_last_file_in_path_trailing_separator(void)
{
// Given a path with trailing separator
#ifdef _WIN32
    const char *path = "c:\\folder1\\folder2\\";
#else
    const char *path = "/folder1/folder2/";
#endif

    // When getting the last file
    const char *last_file = get_last_file_in_path(path);

    // Then it should return empty string
    TEST_ASSERT_EQUAL_STRING("", last_file);
}
