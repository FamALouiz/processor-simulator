#include "unity.h"
#include "word_parser.h"
#include "mem_manager.h"
#include "config_loader.h"
#include <stdio.h>
#include <stdlib.h>

void test_parse_movr_instruction(void)
{
    word *instruction = (word *)malloc(sizeof(word));
    int_to_word(2701131778, instruction);
    int r1Value = 42;
    int r3Value;
    int imm = 2;
    word *r1 = (word *)malloc(sizeof(word));
    word *r3 = (word *)malloc(sizeof(word));
    int_to_word(r1Value, r1);
    reg_write(R1, r1);
    word *check = (word *)malloc(sizeof(word));
    int toBeRead = r1Value + imm;
    mem_read(check, toBeRead);
    int expectedValue;
    word_to_int(check, &expectedValue);
    // MOVR moves value from R1 to R3
    parse(instruction);
    reg_read(R3, r3);
    word_to_int(r3, &r3Value);
    TEST_ASSERT_EQUAL_INT(expectedValue, r3Value);
    free(instruction);
    free(r1);
    free(r3);
}
