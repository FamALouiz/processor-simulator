#include "unity.h"

extern void test_mem_read_and_write(void);
extern void test_reg_read_and_write(void);
extern void test_pipeline_read_and_write(void);
extern void test_memory_boundaries(void);
extern void test_interrupt_functions(void);

void setUp(void);

void tearDown(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_mem_read_and_write);
    RUN_TEST(test_reg_read_and_write);
    RUN_TEST(test_pipeline_read_and_write);
    RUN_TEST(test_memory_boundaries);
    RUN_TEST(test_interrupt_functions);

    return UNITY_END();
}
