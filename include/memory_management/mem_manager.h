#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H
#include "word.h"
#include <assert.h>

//MEMORY SIZE (ROWS)
#define MEM_SIZE 2048
#define REG_SIZE 31
#define DATA_INDEX 1024

//AVAILABLE REGISTERS
//SPECIAL REGISTER
#define R0 32 //READ-ONLY
#define PC 31

//GENREAL PURPOSE REGISTERS
#define R1 0
#define R2 1
#define R3 2
#define R4 3
#define R5 4
#define R6 5
#define R7 6
#define R8 7
#define R9 8
#define R10 9
#define R11 10
#define R12 11
#define R13 12
#define R14 13
#define R15 14
#define R16 15
#define R17 16
#define R18 17
#define R19 18
#define R20 19
#define R21 20
#define R22 21
#define R23 22
#define R24 23
#define R25 24
#define R26 25
#define R27 26
#define R28 27
#define R29 28
#define R30 29
#define R31 30

typedef unsigned int mem_register; 
//The main memory interface
typedef struct
{
    word memory[MEM_SIZE];
    word registers[REG_SIZE];
    word program_counter;
} memory_interface;

static memory_interface main_memory;

//read from memory
void mem_read(word* output, unsigned int index);

//read from memory
void mem_write(const word* data, unsigned int index);

//read from register
void reg_read(mem_register reg, word* output);

//write to register
void reg_write(mem_register reg, const word* data);
#endif