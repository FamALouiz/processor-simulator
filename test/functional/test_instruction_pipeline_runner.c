#include "unity.h"

extern void test_full_instruction_pipeline(void);

void setUp(void);
void tearDown(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_full_instruction_pipeline);

    return UNITY_END();
}
