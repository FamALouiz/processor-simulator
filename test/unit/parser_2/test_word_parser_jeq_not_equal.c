
#include "unity.h"
#include "word_parser.h"
#include "mem_manager.h"
#include "config_loader.h"
#include <stdio.h>
#include <stdlib.h>

#define CONFIG_FILE_PATH "test_config.config"

void init_config(void)
{
    FILE *file = fopen(CONFIG_FILE_PATH, "w");
    if (file == NULL)
    {
        perror("Failed to open config file for writing");
        return;
    }

    // Write valid configuration data
    fprintf(file, "ADD=0000\n");
    fprintf(file, "SUB=0001\n");
    fprintf(file, "MUL=0010\n");
    fprintf(file, "MOVI=0011\n");
    fprintf(file, "JEQ=0100\n");
    fprintf(file, "AND=0101\n");
    fprintf(file, "XORI=0110\n");
    fprintf(file, "JMP=0111\n");
    fprintf(file, "LSL=1000\n");
    fprintf(file, "LSR=1001\n");
    fprintf(file, "MOVR=1010\n");
    fprintf(file, "MOVM=1011\n");

    fclose(file);

    load_properties(CONFIG_FILE_PATH);
}

void setUp(void)
{
    init_config();
}

void tearDown(void)
{
}

void test_parse_jeq_instruction_not_equal(void)
{
    // Setup registers and PC for JEQ test
    int r1Value = 7;
    int r2Value = 5;
    int jumpOffset = 10;
    int originalPC = 0;
    int expectedPC = 1;

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
    word_to_int(pc, &expectedPC);

    // PC should be updated with jump offset
    TEST_ASSERT_EQUAL_INT(0, expectedPC);

    free(instruction);
    free(r1);
    free(r2);
    free(pc);
}