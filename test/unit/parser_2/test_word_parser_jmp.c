#include "unity.h"
#include "word_parser.h"
#include "mem_manager.h"
#include "config_loader.h"
#include <stdio.h>
#include <stdlib.h>

void test_parse_jmp_instruction(void)
{
    // Setup PC for JMP test
    int originalPC = 0;
    int jumpAddress = 100;
    int expectedPC;

    word *instruction = (word *)malloc(sizeof(word));
    int_to_word(1879048292, instruction); // JMP jumpAddress

    word *pc = (word *)malloc(sizeof(word));
    int_to_word(originalPC, pc);
    reg_write(PC, pc); // Assuming PC is a defined register constant

    // Execute JMP instruction
    parse(instruction);

    // Read PC after jump
    reg_read(PC, pc);
    word_to_int(pc, &expectedPC);

    // PC should be set to jump address
    TEST_ASSERT_EQUAL_INT(jumpAddress, expectedPC);

    free(instruction);
    free(pc);
}
