#include "unity.h"

extern void test_branching_instructions(void);
extern void test_not_taken_branch(void);

void setUp(void);
void tearDown(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_branching_instructions);
    RUN_TEST(test_not_taken_branch);

    return UNITY_END();
}
