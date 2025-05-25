#include "unity.h"
#include "word_parser.h"
#include "mem_manager.h"
#include "config_loader.h"
#include <stdio.h>
#include <stdlib.h>

void test_parse_lsr_instruction(void)
{
    word *instruction = (word *)malloc(sizeof(word));
    int_to_word(2432696322, instruction);
    int r1Value = 20;
    int shiftAmount = 2;
    int r3Value;
    word *r1 = (word *)malloc(sizeof(word));
    word *r3 = (word *)malloc(sizeof(word));
    int_to_word(r1Value, r1);
    reg_write(R1, r1);
    // LSR instruction shifts R1 by shiftAmount and stores in R3
    // For LSR, the third parameter in the instruction is the shift amount
    parse(instruction);
    reg_read(R3, r3);
    word_to_int(r3, &r3Value);
    TEST_ASSERT_EQUAL_INT(5, r3Value); // 20 >> 2 = 5
    free(instruction);
    free(r1);
    free(r3);
}
