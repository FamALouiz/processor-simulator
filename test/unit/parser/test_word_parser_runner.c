#include "unity.h"

extern void test_parse_add_instruction(void);
extern void test_parse_sub_instruction(void);
extern void test_parse_end_instruction(void);

void setUp(void);
void tearDown(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_parse_add_instruction);
    RUN_TEST(test_parse_sub_instruction);
    RUN_TEST(test_parse_end_instruction);

    return UNITY_END();
}
