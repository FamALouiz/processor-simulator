#include "unity.h"
#include "word_parser.h"
#include "mem_manager.h"
#include "config_loader.h"
#include <stdio.h>
#include <stdlib.h>

void test_parse_movm_instruction(void)
{
    word *instruction = (word *)malloc(sizeof(word));
    int_to_word(2969567234, instruction);
    int valueToStore = 123;
    int r1Value = 42;
    int readValue;
    int address;

    // R1 will contain the memory address
    word *r1 = (word *)malloc(sizeof(word));
    int_to_word(r1Value, r1);
    reg_write(R1, r1);
    address = r1Value + 2;
    word *r3 = (word *)malloc(sizeof(word));
    int_to_word(valueToStore, r3);
    reg_write(R3, r3);

    // MOVM reads from memory at address in R1 and stores in R3
    parse(instruction);

    // Check that R3 now contains the value from memory
    word *result = (word *)malloc(sizeof(word));
    mem_read(result, address);
    word_to_int(result, &readValue);

    TEST_ASSERT_EQUAL_INT(valueToStore, readValue);

    free(result);
    free(r1);
    free(r3);
    free(instruction);
}
