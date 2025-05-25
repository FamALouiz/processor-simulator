#include "unity.h"
#include "word_parser.h"
#include "mem_manager.h"
#include "config_loader.h"
#include <stdio.h>
#include <stdlib.h>

void test_parse_jeq_instruction(void)
{
    // Setup registers and PC for JEQ test
    int r1Value = 6;
    int r2Value = 6; // Equal to r1 to trigger jump
    int jumpOffset = 10;
    int originalPC = 0;
    int expectedPC = 7 - 2;

    word *instruction = (word *)malloc(sizeof(word));
    int_to_word(1074003975, instruction); // JEQ R1, R2, jumpOffset

    word *r1 = (word *)malloc(sizeof(word));
    word *r2 = (word *)malloc(sizeof(word));
    word *pc = (word *)malloc(sizeof(word));

    int_to_word(r1Value, r1);
    int_to_word(r2Value, r2);
    int_to_word(originalPC, pc);

    reg_write(R1, r1);
    reg_write(R2, r2);
    reg_write(PC, pc); // Assuming PC is a defined register constant

    // Execute JEQ instruction
    parse(instruction);

    // Read PC after jump
    reg_read(PC, pc);
    word_to_int(pc, &originalPC);

    // PC should be updated with jump offset
    TEST_ASSERT_EQUAL_INT(expectedPC, originalPC);

    free(instruction);
    free(r1);
    free(r2);
    free(pc);
}
