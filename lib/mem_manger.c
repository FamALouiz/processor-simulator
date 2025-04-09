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