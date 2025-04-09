#include "word.h"

//MEMORY SIZE (ROWS)
#define MEM_SIZE 2048
#define DATA_INDEX 1024

//The main memory interface
typedef struct
{
    word memory[MEM_SIZE];
} memory_interface;

static memory_interface main_memory;

//read from memory
void mem_read(word* output, unsigned int index);

//read from memory
void mem_write(const word* data, unsigned int index);

