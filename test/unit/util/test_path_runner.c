#include "unity.h"

extern void test_join_paths(void);
extern void test_join_paths_empty(void);
extern void test_join_paths_single(void);
extern void test_get_last_file_in_path(void);
extern void test_get_last_file_in_path_no_separator(void);
extern void test_get_last_file_in_path_trailing_separator(void);

void setUp(void);
void tearDown(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_join_paths);
    RUN_TEST(test_join_paths_empty);
    RUN_TEST(test_join_paths_single);
    RUN_TEST(test_get_last_file_in_path);
    RUN_TEST(test_get_last_file_in_path_no_separator);
    RUN_TEST(test_get_last_file_in_path_trailing_separator);

    return UNITY_END();
}
