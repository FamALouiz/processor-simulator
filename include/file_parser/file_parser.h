#ifndef PARSER_PART1_H
#define PARSER_PART1_H
#include "../memory_management/mem_manager.h"
// Enum for instruction format
typedef enum { R_TYPE, I_TYPE, J_TYPE } Format;

// Instruction format config
typedef struct {
    char mnemonic[10];
    char binary_opcode[5];  // 4-bit binary string (with null terminator)
    Format type;
} InstructionFormat;


// Function declarations
void load_properties(const char* filename);
void parse_and_encode(const char* filename);

#endif
