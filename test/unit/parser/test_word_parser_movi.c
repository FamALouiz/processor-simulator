#include "unity.h"
#include "word_parser.h"
#include "mem_manager.h"
#include "config_loader.h"
#include <stdio.h>
#include <stdlib.h>

void test_parse_movi_instruction(void)
{
    word *instruction = (word *)malloc(sizeof(word));
    int_to_word(822083591, instruction);
    int r3Value;
    word *r3 = (word *)malloc(sizeof(word));
    // MOVI loads an immediate value into R3
    parse(instruction);
    reg_read(R3, r3);
    word_to_int(r3, &r3Value);
    TEST_ASSERT_EQUAL_INT(7, r3Value); // Immediate value 7
    free(instruction);
    free(r3);
}
