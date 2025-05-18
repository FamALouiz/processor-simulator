#ifndef PARSER_PART1_H
#define PARSER_PART1_H
#include "../memory_management/mem_manager.h"

// Enum for instruction format
typedef enum
{
    R_TYPE,
    I_TYPE,
    J_TYPE
} Format;

void parse_and_encode(const char *filename);

#endif
