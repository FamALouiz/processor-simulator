#include "unity.h"
#include "word_parser.h"
#include "mem_manager.h"
#include "config_loader.h"
#include <stdio.h>
#include <stdlib.h>

void test_parse_and_instruction(void)
{
    word *instruction = (word *)malloc(sizeof(word));
    int_to_word(1358962690, instruction);
    int r1Value = 5;
    int r2Value = 3;
    int r3Value;
    word *r1 = (word *)malloc(sizeof(word));
    word *r2 = (word *)malloc(sizeof(word));
    word *r3 = (word *)malloc(sizeof(word));
    int_to_word(r1Value, r1);
    int_to_word(r2Value, r2);
    reg_write(R1, r1);
    reg_write(R2, r2);
    parse(instruction);
    reg_read(R3, r3);
    word_to_int(r3, &r3Value);
    TEST_ASSERT_EQUAL_INT(1, r3Value); // 5 & 3 = 1
    free(instruction);
    free(r1);
    free(r2);
    free(r3);
}
