#include "file_parser.h"
#include "logger.h"
#include "config_loader.h"

void to_binary(char *bin, int value, int bits)
{
    bin[bits] = '\0'; // Null-terminate the string
    for (int i = bits - 1; i >= 0; i--)
    {
        bin[i] = (value & 1) ? '1' : '0';
        value >>= 1;
    }
}

Format get_format(const char *mnemonic)
{
    // R-Type operations
    if (strcmp(mnemonic, "ADD") == 0 ||
        strcmp(mnemonic, "SUB") == 0 ||
        strcmp(mnemonic, "MUL") == 0 ||
        strcmp(mnemonic, "AND") == 0 ||
        strcmp(mnemonic, "LSL") == 0 ||
        strcmp(mnemonic, "LSR") == 0)
        return R_TYPE;

    // I-Type operations
    if (strcmp(mnemonic, "MOVI") == 0 ||
        strcmp(mnemonic, "JEQ") == 0 ||
        strcmp(mnemonic, "XORI") == 0 ||
        strcmp(mnemonic, "MOVR") == 0 ||
        strcmp(mnemonic, "MOVM") == 0)
        return I_TYPE;

    // J-Type operations (only JMP for now)
    return J_TYPE;
}

int get_register_index(const char *reg_str)
{
    if (strcmp(reg_str, "R0") == 0)
        return 0; // Always zero
    if (reg_str[0] == 'R')
        return atoi(&reg_str[1]) - 1;
    return -1;
}

void parse_and_encode(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        error("Could not open assembly file");
        exit(1);
    }

    char line[100], mnemonic[10], op1[10], op2[10], op3[10];
    int instruction_index = 0;
    while (fgets(line, sizeof(line), file))
    {
        char message[256];
        snprintf(message, sizeof(message), "Current line: %s", line);
        info(message);

        // Remove comments: truncate line at '#' if present
        char *comment = strchr(line, '#');
        if (comment)
            *comment = '\0';

        // Skip empty lines
        char *trim = line;
        while (*trim == ' ' || *trim == '\t' || *trim == '\n')
            trim++;
        if (*trim == '\0')
            continue;

        // Initialize operands to empty strings
        mnemonic[0] = op1[0] = op2[0] = op3[0] = '\0';

        // Tokenize the line to extract mnemonic and operands
        char *token = strtok(line, " \t\n");
        if (token)
        {
            strncpy(mnemonic, token, sizeof(mnemonic) - 1);
            mnemonic[sizeof(mnemonic) - 1] = '\0';
        }
        token = strtok(NULL, " ,\t\n");
        if (token)
        {
            strncpy(op1, token, sizeof(op1) - 1);
            op1[sizeof(op1) - 1] = '\0';
        }
        token = strtok(NULL, " ,\t\n");
        if (token)
        {
            strncpy(op2, token, sizeof(op2) - 1);
            op2[sizeof(op2) - 1] = '\0';
        }
        token = strtok(NULL, " ,\t\n");
        if (token)
        {
            strncpy(op3, token, sizeof(op3) - 1);
            op3[sizeof(op3) - 1] = '\0';
        }

        char *op_bin = NULL;
        Format type;

        get_config(mnemonic, &op_bin, &type);

        if (!op_bin)
        {
            char message[256];
            snprintf(message, "Unknown instruction: %s\n", mnemonic);
            warn(message);
            continue;
        }

        char bin[33], r1_bin[6], r2_bin[6], r3_bin[6];
        char shamt_bin[14], imm_bin[19], addr_bin[29];

        if (type == R_TYPE)
        {
            int r1 = get_register_index(&op1);
            int r2 = get_register_index(&op2);
            int r3 = (strcmp(mnemonic, "LSL") == 0 || strcmp(mnemonic, "LSR") == 0) ? 0 : get_register_index(&op3);
            int shamt = (strcmp(mnemonic, "LSL") == 0 || strcmp(mnemonic, "LSR") == 0) ? get_register_index(&op3) : 0;

            to_binary(r1_bin, r1, 5);
            to_binary(r2_bin, r2, 5);
            to_binary(r3_bin, r3, 5);
            to_binary(shamt_bin, shamt, 13);

            sprintf(bin, "%s%s%s%s%s", op_bin, r1_bin, r2_bin, r3_bin, shamt_bin);
        }
        else if (type == I_TYPE)
        {
            int r1 = get_register_index(&op1);
            int r2 = (strcmp(mnemonic, "MOVI") == 0) ? 0 : get_register_index(&op2);
            int imm = atoi(op3);

            to_binary(r1_bin, r1, 5);
            to_binary(r2_bin, r2, 5);
            to_binary(imm_bin, imm, 18);

            sprintf(bin, "%s%s%s%s", op_bin, r1_bin, r2_bin, imm_bin);
        }
        else if (type == J_TYPE)
        {
            int addr = atoi(op1);
            to_binary(addr_bin, addr, 28);
            sprintf(bin, "%s%s", op_bin, addr_bin);
        }

        word *bin_word = (word *)malloc(sizeof(word));

        unsigned int value = 0;
        for (int i = 0; i < 32; i++)
        {
            value <<= 1;
            if (bin[i] == '1')
                value |= 1;
        }

        (*bin_word)[0] = (unsigned char)((value >> 24) & 0xFF);
        (*bin_word)[1] = (unsigned char)((value >> 16) & 0xFF);
        (*bin_word)[2] = (unsigned char)((value >> 8) & 0xFF);
        (*bin_word)[3] = (unsigned char)(value & 0xFF);
        mem_write(bin_word, instruction_index++);
        free(bin_word); // Free memory after use
    }

    word *end_word = (word *)malloc(sizeof(word));
    (*end_word)[0] = 0xFF;
    (*end_word)[1] = 0xFF;
    (*end_word)[2] = 0xFF;
    (*end_word)[3] = 0xFF;
    mem_write(end_word, instruction_index++);
    free(end_word);

    fclose(file);
}