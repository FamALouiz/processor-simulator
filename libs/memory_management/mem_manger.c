#include "mem_manager.h"
#include "logger.h"
#include <string.h>
#include <stdlib.h>

void mem_read(word *output, unsigned int index)
{
    if (index < 0 || index >= MEM_SIZE)
    {
        char *message = (char *)malloc(sizeof(char) * 1024);
        sprintf(message, "Index must be greater than or equal to 0 and less than %d", MEM_SIZE);
        error(message);
        free(message);
        return;
    }
    assert(index >= 0 && index < MEM_SIZE);

    (*output)[0] = main_memory.memory[index][0];
    (*output)[1] = main_memory.memory[index][1];
    (*output)[2] = main_memory.memory[index][2];
    (*output)[3] = main_memory.memory[index][3];

    char message[50];
    sprintf(message, "Read memory slot %d", index);
    info(message);
}

void mem_write(const word *data, unsigned int index)
{
    if (index < 0 || index >= MEM_SIZE)
    {
        char *message = (char *)malloc(sizeof(char) * 1024);
        sprintf(message, "Index must be greater than or equal to 0 and less than %d", MEM_SIZE);
        error(message);
        free(message);
        return;
    }
    assert(index >= 0 && index < MEM_SIZE);

    main_memory.memory[index][0] = (*data)[0];
    main_memory.memory[index][1] = (*data)[1];
    main_memory.memory[index][2] = (*data)[2];
    main_memory.memory[index][3] = (*data)[3];

    char message[50];
    sprintf(message, "Written memory slot %d", index);
    info(message);
}

void reg_read(mem_register reg, word *output)
{

    if (reg >= R1 && reg < RZERO)
    {
        char *message = "Register not found";
        error(message);
        return;
    }
    assert(reg >= R1 && reg <= RZERO);

    if (reg >= R1 && reg <= R31)
    {
        // General Purpose Register
        (*output)[0] = main_memory.registers[reg][0];
        (*output)[1] = main_memory.registers[reg][1];
        (*output)[2] = main_memory.registers[reg][2];
        (*output)[3] = main_memory.registers[reg][3];

        char message[50];
        sprintf(message, "Read from general purpose register R%d", reg);
        info(message);
    }
    else if (reg == RZERO)
    {
        // Zero Register
        (*output)[0] = '0';
        (*output)[1] = '0';
        (*output)[2] = '0';
        (*output)[3] = '0';

        char message[50];
        sprintf(message, "Read from zero register RZERO");
        info(message);
    }
    else
    {
        // PC Register
        (*output)[0] = main_memory.program_counter[0];
        (*output)[1] = main_memory.program_counter[1];
        (*output)[2] = main_memory.program_counter[2];
        (*output)[3] = main_memory.program_counter[3];

        char message[50];
        sprintf(message, "Read from program counter register PC");
        info(message);
    }
}

void reg_write(mem_register reg, const word *data)
{
    if (reg < R1 || reg > PC)
    {
        char *message = "Invalid register specified";
        error(message);
        return;
    }
    assert(reg >= R1 && reg <= PC);

    if (reg >= R1 && reg <= R31)
    {
        // General Purpose Register
        main_memory.registers[reg][0] = (*data)[0];
        main_memory.registers[reg][1] = (*data)[1];
        main_memory.registers[reg][2] = (*data)[2];
        main_memory.registers[reg][3] = (*data)[3];

        char message[50];
        sprintf(message, "Written to general purpose register R%d", reg);
        info(message);
    }
    else
    {
        // PC Register
        main_memory.program_counter[0] = (*data)[0];
        main_memory.program_counter[1] = (*data)[1];
        main_memory.program_counter[2] = (*data)[2];
        main_memory.program_counter[3] = (*data)[3];

        char message[50];
        sprintf(message, "Written to program counter register PC");
        info(message);
    }
}