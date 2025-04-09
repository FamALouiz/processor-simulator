#include "../include/mem_manager.h"

void mem_read(word* output, unsigned int index){

    assert(index >=0 && index < MEM_SIZE);
    
    (*output)[0] = main_memory.memory[index][0];
    (*output)[1] = main_memory.memory[index][1];
    (*output)[2] = main_memory.memory[index][2];
    (*output)[3] = main_memory.memory[index][3];
}


void mem_write(const word* data, unsigned int index)
{
    assert(index >=0 && index < MEM_SIZE);

    main_memory.memory[index][0] = (*data)[0];
    main_memory.memory[index][1] = (*data)[1];
    main_memory.memory[index][2] = (*data)[2];
    main_memory.memory[index][3] = (*data)[3];
}

void reg_read(mem_register reg, word* output){
    assert(reg >= R1 && reg <= RZERO);

    if(reg >= R1 && reg <= R31)
    {
        //General Purpose Register
        (*output)[0] = main_memory.registers[reg][0];
        (*output)[1] = main_memory.registers[reg][1];
        (*output)[2] = main_memory.registers[reg][2];
        (*output)[3] = main_memory.registers[reg][3];
    }else if (reg == RZERO)
    {
        //Zero Register
        (*output)[0] = '0';
        (*output)[1] = '0';
        (*output)[2] = '0';
        (*output)[3] = '0';
    }else{
        //PC Register
        (*output)[0] = main_memory.program_counter[0];
        (*output)[1] = main_memory.program_counter[1];
        (*output)[2] = main_memory.program_counter[2];
        (*output)[3] = main_memory.program_counter[3];
    }
    
}

void reg_write(mem_register reg, const word* data)
{
    assert(reg >= R1 && reg <= PC);

    if(reg >= R1 && reg <= R31)
    {
        //General Purpose Register
        main_memory.registers[reg][0] = (*data)[0];
        main_memory.registers[reg][1] = (*data)[1];
        main_memory.registers[reg][2] = (*data)[2];
        main_memory.registers[reg][3] = (*data)[3];
       
    }else{
        //PC Register
        main_memory.program_counter[0] = (*data)[0]; 
        main_memory.program_counter[1] = (*data)[1];
        main_memory.program_counter[2] = (*data)[2];
        main_memory.program_counter[3] = (*data)[3];
    }    
}