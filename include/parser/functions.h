#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <mem_manager.h>
#include <word.h>

// Arithmetic operations
void add(mem_register Output, mem_register Reg0, mem_register Reg1);
void sub(mem_register Output, mem_register Reg0, mem_register Reg1);
void mul(mem_register Output, mem_register Reg0, mem_register Reg1);

// Move immediate
void movi(mem_register Output, word imm);

// Logical operations
void and (mem_register Output, mem_register Reg0, mem_register Reg1);
void xori(mem_register Output, mem_register Reg0, int imm);

// Shift operations
void lsl(mem_register Output, mem_register Reg0, int shamt);
void lsr(mem_register Output, mem_register Reg0, int shamt);

// Jump and branch
void jeq(mem_register Reg0, mem_register Reg1, int imm);
void jmp(int address);

// Memory operations
void movr(mem_register Output, mem_register Reg0, int imm);
void movm(mem_register Reg0, mem_register Reg1, int imm);

#endif // FUNCTIONS_H