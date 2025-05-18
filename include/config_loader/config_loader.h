#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H
#include "file_parser.h"

// Instruction format config
typedef struct
{
    char mnemonic[10];
    char binary_opcode[5]; // 4-bit binary string (with null terminator)
    Format type;
} InstructionFormat;

// Function declarations
void load_properties(const char *filename);

void get_config(const char *mnemonic, char **bin_opcode, Format *type);

#endif // CONFIG_LOADER_H