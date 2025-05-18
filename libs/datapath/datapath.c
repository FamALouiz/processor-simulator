#include "include/datapath/datapath.h"

//Increment cycle
void nextCycle(int* cycles)
{ (*cycles)++; }

int getCycle(int* cycles)
{ return *cycles;}

//initialize program counter to a particular value
void initProgramCounter(unsigned int start)
{
    const word zero = {0,0,0,0};
    reg_write(PC, &zero);

}
