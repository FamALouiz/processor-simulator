#include "unity.h"

extern void test_add_function(void);
extern void test_sub_function(void);
extern void test_mul_function(void);
extern void test_and_function(void);
extern void test_movi_function(void);
extern void test_lsl_function(void);
extern void test_lsr_function(void);
extern void test_xori_function(void);

void setUp(void);
void tearDown(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_add_function);
    RUN_TEST(test_sub_function);
    RUN_TEST(test_mul_function);
    RUN_TEST(test_and_function);
    RUN_TEST(test_movi_function);
    RUN_TEST(test_lsl_function);
    RUN_TEST(test_lsr_function);
    RUN_TEST(test_xori_function);

    return UNITY_END();
}
