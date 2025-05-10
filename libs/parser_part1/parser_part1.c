#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/parser_part1/parser_part1.h"

InstructionFormat config[12];
int configCount = 0;

Format get_format(const char* mnemonic) {
    if (strcmp(mnemonic, "ADD") == 0 || strcmp(mnemonic, "SUB") == 0 || strcmp(mnemonic, "MUL") == 0 ||
        strcmp(mnemonic, "AND") == 0 || strcmp(mnemonic, "LSL") == 0 || strcmp(mnemonic, "LSR") == 0)
        return R_TYPE;
    if (strcmp(mnemonic, "MOVI") == 0 || strcmp(mnemonic, "JEQ") == 0 || strcmp(mnemonic, "XORI") == 0 ||
        strcmp(mnemonic, "MOVR") == 0 || strcmp(mnemonic, "MOVM") == 0)
        return I_TYPE;
    return J_TYPE;
}

int get_register_index(const char* reg_str) {
    if (strcmp(reg_str, "R0") == 0) return 0;      // Always zero
    if (reg_str[0] == 'R') return atoi(&reg_str[1]) - 1;
    return -1;
}

void load_properties(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Could not open config file");
        exit(1);
    }

    char line[100], mnemonic[10], bin_opcode[5];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || strchr(line, '=') == NULL) continue;

        sscanf(line, "%[^=]=%s", mnemonic, bin_opcode);

        strcpy(config[configCount].mnemonic, mnemonic);
        strcpy(config[configCount].binary_opcode, bin_opcode);
        config[configCount].type = get_format(mnemonic);
        configCount++;
    }

    fclose(file);
}

void parse_and_encode(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Could not open assembly file");
        exit(1);
    }

    char line[100], mnemonic[10], op1[10], op2[10], op3[10];
    int instruction_index = 0;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\n' || line[0] == '#') continue;

        sscanf(line, "%s %s %s %s", mnemonic, op1, op2, op3);
        char* op_bin = NULL;
        Format type;

        for (int i = 0; i < configCount; i++) {
            if (strcmp(config[i].mnemonic, mnemonic) == 0) {
                op_bin = config[i].binary_opcode;
                type = config[i].type;
                break;
            }
        }

        if (!op_bin) {
            printf("Unknown instruction: %s\n", mnemonic);
            continue;
        }

        char bin[33], r1_bin[6], r2_bin[6], r3_bin[6];
        char shamt_bin[14], imm_bin[19], addr_bin[29];

        if (type == R_TYPE) {
            int r1 = atoi(&op1[1]);
            int r2 = atoi(&op2[1]);
            int r3 = (strcmp(mnemonic, "LSL") == 0 || strcmp(mnemonic, "LSR") == 0) ? 0 : atoi(&op3[1]);
            int shamt = (strcmp(mnemonic, "LSL") == 0 || strcmp(mnemonic, "LSR") == 0) ? atoi(op3) : 0;

            to_binary(r1_bin, r1, 5);
            to_binary(r2_bin, r2, 5);
            to_binary(r3_bin, r3, 5);
            to_binary(shamt_bin, shamt, 13);

            sprintf(bin, "%s%s%s%s%s", op_bin, r1_bin, r2_bin, r3_bin, shamt_bin);

        } else if (type == I_TYPE) {
            int r1 = atoi(&op1[1]);
            int r2 = (strcmp(mnemonic, "MOVI") == 0) ? 0 : atoi(&op2[1]);
            int imm = atoi(op3);

            to_binary(r1_bin, r1, 5);
            to_binary(r2_bin, r2, 5);
            to_binary(imm_bin, imm, 18);

            sprintf(bin, "%s%s%s%s", op_bin, r1_bin, r2_bin, imm_bin);

        } else if (type == J_TYPE) {
            int addr = atoi(op1);
            to_binary(addr_bin, addr, 28);
            sprintf(bin, "%s%s", op_bin, addr_bin);
        }

        mem_write(bin, instruction_index++);
    }

    fclose(file);
}



