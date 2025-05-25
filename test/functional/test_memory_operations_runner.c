#include "unity.h"

extern void test_memory_operations(void);
extern void test_memory_operations_with_offset(void);

void setUp(void);
void tearDown(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_memory_operations);
    RUN_TEST(test_memory_operations_with_offset);

    return UNITY_END();
}
