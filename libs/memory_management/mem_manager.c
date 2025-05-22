#include "mem_manager.h"


void mem_read(word *output, unsigned int index)
{
    // Unsigned int can't be < 0, so we only need to check upper bound
    if (index >= MEM_SIZE)
    {
        char message[128];
        snprintf(message, sizeof(message), "Index must be less than %d", MEM_SIZE);
        error(message);
        return;
    }

    (*output)[0] = main_memory.memory[index][0];
    (*output)[1] = main_memory.memory[index][1];
    (*output)[2] = main_memory.memory[index][2];
    (*output)[3] = main_memory.memory[index][3];

    char message[50];
    sprintf(message, "Read memory slot %d", index);
    // info(message);   
}

void mem_write(const word *data, unsigned int index)
{
    // Unsigned int can't be < 0, so we only need to check upper bound
    if (index >= MEM_SIZE)
    {
        char message[128];
        snprintf(message, sizeof(message), "Index must be less than %d", MEM_SIZE);
        error(message);
        return;
    }

    main_memory.memory[index][0] = (*data)[0];
    main_memory.memory[index][1] = (*data)[1];
    main_memory.memory[index][2] = (*data)[2];
    main_memory.memory[index][3] = (*data)[3];

    char message[50];
    sprintf(message, "Written memory slot %d", index);
    // info(message);
}

void reg_read(mem_register reg, word *output)
{
    if (reg < R1 || reg > R0)
    {
        char *message = "Invalid register specified";
        error(message);
        return;
    }

    if (reg >= R1 && reg <= R31)
    {
        // General Purpose Register
        (*output)[0] = main_memory.registers[reg][0];
        (*output)[1] = main_memory.registers[reg][1];
        (*output)[2] = main_memory.registers[reg][2];
        (*output)[3] = main_memory.registers[reg][3];

        char message[50];
        sprintf(message, "Read from general purpose register R%d", reg);
        // info(message);
    }
    else if (reg == R0)
    {
        // Zero Register
        (*output)[0] = 0;
        (*output)[1] = 0;
        (*output)[2] = 0;
        (*output)[3] = 0;

        char message[50];
        sprintf(message, "Read from zero register R0");
        rf(message);
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
        // info(message);
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

    if (reg >= R1 && reg <= R31)
    {
        // General Purpose Register
        main_memory.registers[reg][0] = (*data)[0];
        main_memory.registers[reg][1] = (*data)[1];
        main_memory.registers[reg][2] = (*data)[2];
        main_memory.registers[reg][3] = (*data)[3];

        char message[50];
        sprintf(message, "Written to general purpose register R%d", reg);
        // info(message);
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
        // info(message);
    }
}

void pipeline_read(mem_register reg, word *output)
{

    if ( reg < RIF || reg > RWB )
    {
        char *message = "Register not found";
        error(message);
        return;
    }
    assert(reg >= RIF && reg <= RWB);
    
    (*output)[0] = main_memory.pipeline_registers[reg - RIF][0];
    (*output)[1] = main_memory.pipeline_registers[reg - RIF][1];
    (*output)[2] = main_memory.pipeline_registers[reg - RIF][2];
    (*output)[3] = main_memory.pipeline_registers[reg - RIF][3];
    

}

void pipeline_write(mem_register reg, const word *data)
{
    if (reg < RIF || reg > RWB)
    {
        char *message = "Invalid register specified";
        error(message);
        return;
    }
    assert(reg >= RIF && reg <= RWB);

    
    main_memory.pipeline_registers[reg - RIF][0] = (*data)[0];
    main_memory.pipeline_registers[reg - RIF][1] = (*data)[1];
    main_memory.pipeline_registers[reg - RIF][2] = (*data)[2];
    main_memory.pipeline_registers[reg - RIF][3] = (*data)[3];
    
}
void set_interrupt()
{
    printf("SETTING");
    word* one = (word*)malloc(sizeof(word));
    reg_read(R0, one);
    int n;
    word_to_int(one, &n);
    n = 1;
    int_to_word(n, one);

    pipeline_write(RWB, one);
}
void release_interrupt()
{
    word* zero = (word*)malloc(sizeof(word));
    reg_read(R0, zero);
    pipeline_write(RWB, zero);
}

int return_interrupt()
{
    word* value = (word*)malloc(sizeof(word));
    pipeline_read(RWB, value);

    int final;
    word_to_int(value, &final);

    return final;
}