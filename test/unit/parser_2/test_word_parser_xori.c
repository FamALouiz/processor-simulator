#include "unity.h"
#include "word_parser.h"
#include "mem_manager.h"
#include "config_loader.h"
#include <stdio.h>
#include <stdlib.h>

void test_parse_xori_instruction(void)
{
    word *instruction = (word *)malloc(sizeof(word));
    int_to_word(1627389954, instruction);
    int r1Value = 5;
    int r3Value;
    word *r1 = (word *)malloc(sizeof(word));
    word *r3 = (word *)malloc(sizeof(word));
    int_to_word(r1Value, r1);
    reg_write(R1, r1);
    // XORI instruction XORs R1 with immediate value and stores in R3
    parse(instruction);
    reg_read(R3, r3);
    word_to_int(r3, &r3Value);
    TEST_ASSERT_EQUAL_INT(7, r3Value); // 5 ^ 2 = 7
    free(instruction);
    free(r1);
    free(r3);
}
