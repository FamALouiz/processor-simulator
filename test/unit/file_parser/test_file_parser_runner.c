#include "unity.h"

extern void test_parse_and_encode_simple_program(void);

void setUp(void);
void tearDown(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_parse_and_encode_simple_program);

    return UNITY_END();
}
