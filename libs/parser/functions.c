#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mem_manager.h>
#include <word.h>
#include <logger.h>

//  void add(mem_register Output, mem_register Reg0, mem_register Reg1){
//     word OperandA;
//     reg_read(Reg0, OperandA);
//     word OperandB;
//     reg_read(Reg1, OperandB);
//     word Result;
//     int carry=0;
//     for(int i=3;i>=0;i++){
//         int OpA = (int) OperandA[i];
//         int OpB = (int) OperandB[i];
//         int sum = OpA + OpB+ carry;
//         carry = sum & 100000000;
//         Result[i] = sum & 11111111;
//     }
//     //if carry = 1 then numbers addition exceed 32 bits
//     reg_write(Output, Result);
// }

//  TTTTTTTTTTTTTT   OOOOOOOOOOOO   TTTTTTTTTTTTTT   TTTTTTTTTTTTTT  EEEEEEEEE   NNN        NNN   HHH      HHH   AAAAAAAAAAAAAA   MMMMM    MMMM
//       TTTT       OOO        OOO       TTTT             TTTT       EEE         NNNN       NNN   HHH      HHH   AAA        AAA   MMMMMM  MMMMM
//       TTTT       OOO        OOO       TTTT             TTTT       EEE         NNNNN      NNN   HHH      HHH   AAA        AAA   MMM MMMM MMMM
//       TTTT       OOO        OOO       TTTT             TTTT       EEEEEEEE    NNN NNN    NNN   HHHHHHHHHHHH   AAAAAAAAAAAAAA   MMM  MM  MMMM
//       TTTT       OOO        OOO       TTTT             TTTT       EEE         NNN  NNN   NNN   HHH      HHH   AAA        AAA   MMM      MMMM
//       TTTT       OOO        OOO       TTTT             TTTT       EEE         NNN   NNN  NNN   HHH      HHH   AAA        AAA   MMM      MMMM
//       TTTT        OOOOOOOOOOOO        TTTT             TTTT       EEEEEEEE    NNN    NNNNNNN   HHH      HHH   AAA        AAA   MMM      MMMM

void add(mem_register Output, mem_register Reg0, mem_register Reg1)
{
    word OperandA;
    reg_read(Reg0, OperandA);
    word OperandB;
    reg_read(Reg1, OperandB);
    word Result;
    int OpA = (OperandA[0] << 24) | (OperandA[1] << 16) | (OperandA[2] << 8) | OperandA[3];
    int OpB = (OperandB[0] << 24) | (OperandB[1] << 16) | (OperandB[2] << 8) | OperandB[3];
    int Res = OpA + OpB;
    unsigned char a = (Res >> 24) & 255;
    unsigned char b = (Res >> 16) & 255;
    unsigned char c = (Res >> 8) & 255;
    unsigned char d = Res & 255;
    Result[0] = a;
    Result[1] = b;
    Result[2] = c;
    Result[3] = d;
    reg_write(Output, Result);
}

void sub(mem_register Output, mem_register Reg0, mem_register Reg1)
{
    word OperandA;
    reg_read(Reg0, OperandA);
    word OperandB;
    reg_read(Reg1, OperandB);
    word Result;
    int OpA = (OperandA[0] << 24) | (OperandA[1] << 16) | (OperandA[2] << 8) | OperandA[3];
    int OpB = (OperandB[0] << 24) | (OperandB[1] << 16) | (OperandB[2] << 8) | OperandB[3];
    int Res = OpA - OpB;
    unsigned char a = Res >> 24 & 255;
    unsigned char b = Res >> 16 & 255;
    unsigned char c = Res >> 8 & 255;
    unsigned char d = Res & 255;
    Result[0] = a;
    Result[1] = b;
    Result[2] = c;
    Result[3] = d;
    reg_write(Output, Result);
}
void mul(mem_register Output, mem_register Reg0, mem_register Reg1)
{
    word OperandA;
    reg_read(Reg0, OperandA);
    word OperandB;
    reg_read(Reg1, OperandB);
    word Result;
    int OpA = (OperandA[0] << 24) | (OperandA[1] << 16) | (OperandA[2] << 8) | OperandA[3];
    int OpB = (OperandB[0] << 24) | (OperandB[1] << 16) | (OperandB[2] << 8) | OperandB[3];
    int Res = OpA * OpB;
    unsigned char a = Res >> 24 & 255;
    unsigned char b = Res >> 16 & 255;
    unsigned char c = Res >> 8 & 255;
    unsigned char d = Res & 255;
    Result[0] = a;
    Result[1] = b;
    Result[2] = c;
    Result[3] = d;
    reg_write(Output, Result);
}
void movi(mem_register Output, word *imm)
{
    reg_write(Output, &imm);
}
void jeq(mem_register Reg0, mem_register Reg1, int imm)
{
    word PCn;
    reg_read(PC, PCn);
    int PCint = (PCn[0] << 24) | (PCn[1] << 16) | (PCn[2] << 8) | PCn[3];

    word* reg0_content = (word*)malloc(sizeof(word));
    word* reg1_content = (word*)malloc(sizeof(word));

    reg_read(Reg0, reg0_content);
    reg_read(Reg1, reg1_content);

    unsigned int r0, r1;
    word_to_int(reg0_content, &r0);
    word_to_int(reg1_content, &r1);
    if (r0 == r1)
    {
        PCint += imm -2;
        unsigned char a = PCint >> 24 & 255;
        unsigned char b = PCint >> 16 & 255;
        unsigned char c = PCint >> 8 & 255;
        unsigned char d = PCint & 255;
        PCn[0] = a;
        PCn[1] = b;
        PCn[2] = c;
        PCn[3] = d;
        reg_write(PC, PCn);
    }

    warn("RUNNING JEQ");
    set_interrupt();
}
void and(mem_register Output, mem_register Reg0, mem_register Reg1)
{
    word OperandA;
    reg_read(Reg0, OperandA);
    word OperandB;
    reg_read(Reg1, OperandB);
    word Result;

    Result[0] = OperandA[0] & OperandB[0];
    Result[1] = OperandA[1] & OperandB[1];
    Result[2] = OperandA[2] & OperandB[2];
    Result[3] = OperandA[3] & OperandB[3];
    reg_write(Output, Result);
}
void xori(mem_register Output, mem_register Reg0, int imm)
{
    word Reg0word;
    reg_read(Reg0, Reg0word);
    word immword;
    unsigned char a = imm >> 24 & 255;
    unsigned char b = imm >> 16 & 255;
    unsigned char c = imm >> 8 & 255;
    unsigned char d = imm & 255;
    a = a ^ Reg0word[0];
    b = b ^ Reg0word[1];
    c = c ^ Reg0word[2];
    d = d ^ Reg0word[3];
    immword[0] = a;
    immword[1] = b;
    immword[2] = c;
    immword[3] = d;
    reg_write(Output, immword);
}
// address is int containing bits;
void jmp(int address)
{
    word PCn;
    reg_read(PC, PCn);
    unsigned char a = (address >> 24) & 15;
    unsigned char aa = PCn[0] & 240;
    unsigned char aaa = aa | a;
    unsigned char b = (address >> 16) & 255;
    unsigned char c = (address >> 8) & 255;
    unsigned char d = address & 255;
    PCn[0] = aaa;
    PCn[1] = b;
    PCn[2] = c;
    PCn[3] = d;
    reg_write(PC, &PCn);

    //Write interrupt
    set_interrupt();
}

void lsl(mem_register Output, mem_register Reg0, int shamt)
{
    word OperandA;
    reg_read(Reg0, OperandA);
    unsigned int Res = (OperandA[0] << 24) | (OperandA[1] << 16) | (OperandA[2] << 8) | OperandA[3];
    Res = Res << shamt;
    word Result;
    unsigned char a = Res >> 24 & 255;
    unsigned char b = Res >> 16 & 255;
    unsigned char c = Res >> 8 & 255;
    unsigned char d = Res & 255;
    Result[0] = a;
    Result[1] = b;
    Result[2] = c;
    Result[3] = d;
    reg_write(Output, Result);
}
void lsr(mem_register Output, mem_register Reg0, int shamt)
{
    word OperandA;
    reg_read(Reg0, OperandA);
    unsigned int Res = (OperandA[0] << 24) | (OperandA[1] << 16) | (OperandA[2] << 8) | OperandA[3];
    Res = Res >> shamt;
    word Result;
    unsigned char a = Res >> 24 & 255;
    unsigned char b = Res >> 16 & 255;
    unsigned char c = Res >> 8 & 255;
    unsigned char d = Res & 255;
    Result[0] = a;
    Result[1] = b;
    Result[2] = c;
    Result[3] = d;
    reg_write(Output, Result);
}
// if imm is int which is a number
void movr(mem_register Output, mem_register Reg0, int imm)
{
    word OperandA;
    reg_read(Reg0, OperandA);
    unsigned int OpA = (OperandA[0] << 24) | (OperandA[1] << 16) | (OperandA[2] << 8) | OperandA[3];
    unsigned int temp = OpA + imm;
    word Result;
    mem_read(Result, temp);
    reg_write(Output, Result);
}
void movm(mem_register Reg0, mem_register Reg1, int imm)
{
    word OperandA;
    reg_read(Reg1, OperandA);
    unsigned int OpA = (OperandA[0] << 24) | (OperandA[1] << 16) | (OperandA[2] << 8) | OperandA[3];
    unsigned int temp = OpA + imm;
    word Result;
    reg_read(Reg0, Result);
    mem_write(Result, temp);
}
