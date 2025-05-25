#include "unity.h"

// extern void test_parse_add_instruction(void);
// extern void test_parse_sub_instruction(void);
// extern void test_parse_mul_instruction(void);
// extern void test_parse_and_instruction(void);
// extern void test_parse_lsl_instruction(void);
// extern void test_parse_lsr_instruction(void);
// extern void test_parse_movi_instruction(void);
extern void test_parse_jeq_instruction(void);
extern void test_parse_xori_instruction(void);
extern void test_parse_movr_instruction(void);
extern void test_parse_movm_instruction(void);
extern void test_parse_jmp_instruction(void);
extern void test_parse_jeq_instruction_not_equal(void);
// extern void test_parse_end_instruction(void);

void setUp(void);
void tearDown(void);

int main(void)
{
    UNITY_BEGIN();

    // RUN_TEST(test_parse_add_instruction);
    // RUN_TEST(test_parse_sub_instruction);
    // RUN_TEST(test_parse_mul_instruction);
    // RUN_TEST(test_parse_and_instruction);
    // RUN_TEST(test_parse_lsl_instruction);
    // RUN_TEST(test_parse_lsr_instruction);
    // RUN_TEST(test_parse_movi_instruction);
    RUN_TEST(test_parse_jeq_instruction);
    RUN_TEST(test_parse_xori_instruction);
    RUN_TEST(test_parse_movr_instruction);
    RUN_TEST(test_parse_movm_instruction);
    RUN_TEST(test_parse_jmp_instruction);
    RUN_TEST(test_parse_jeq_instruction_not_equal);
    // RUN_TEST(test_parse_end_instruction);

    return UNITY_END();
}
