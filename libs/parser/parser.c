#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mem_manager.h>
#include <word.h>
#include <string.h>
#include <stdlib.h>
#include <logger.h>
#include "functions.h"

char *preParse(word *word)
{ // this is for iterating over the word to convert it to bits
    int res = 0;
    char binaryS[32];
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            res = (int)word[i] & (1 << i);
            if (res == 0)
            {
                binaryS[j * 8 + i] = '0';
            }
            else if (res == 1)
            {
                binaryS[j * 8 + i] = '1';
            }
        }
    }
    return binaryS;
}

int binToDec(char bin[])
{ // to convert binary numbers to int to be able to deal with them easily
    int res = 0;
    int exponent = 1;
    int length = sizeof(bin) / sizeof(bin[0]);
    for (int i = 0; i < length; i++)
    {
        if (i == length - 1)
        { // if the loop is at the last bit of the binary number string
            res = res + atoi(bin[0]) * exponent;
        }
        else
        {
            res = res + atoi(bin[0]) * exponent;
            exponent = exponent * 2;
            memmove(bin, bin + 1, strlen(bin)); // shift string left by one to remove the first bit
            int lenofBin = strlen(bin);
            bin[lenofBin - 1] = '\0';
        }
    }
    return res;
}
void parse(word *word)
{
    char *inst = preParse(word);
    char opCode[4];

    for (int i = 0; i < 4; i++)
    { // to get the first 4 bits of each binary instruction
        opCode[i] = inst[i];
    }
    int opCodeInt = binToDec(opCode); // converts the 4 bits from string to int and then to decimal
    char shamt[13];
    char imm[18];
    char addr[28];
    char firstRegS[5];
    char secondRegS[5];
    char thirdRegS[5]; // in case of R type

    for (int i = 4; i < 9; i++)
    { // get the binary representation of the first register
        firstRegS[i - 4] = inst[i];
    }
    for (int i = 9; i < 14; i++)
    { // get the binary representation of the second register
        secondRegS[i - 9] = inst[i];
    }
    for (int i = 14; i < 19; i++)
    { // get the binary representation of the third register
        thirdRegS[i - 9] = inst[i];
    }
    // in case of R type
    for (int i = 19; i < 32; i++)
    { // get the binary representation of the shift amount value
        shamt[i - 19] = inst[i];
    }
    // in case of I type
    for (int i = 14; i < 32; i++)
    { // get the binary representation of the immediate value
        imm[i - 14] = inst[i];
    }
    // in case of J type
    for (int i = 4; i < 32; i++)
    { // get the binary representation of the address value
        addr[i - 4] = inst[i];
    }
    int firstReg = binToDec(firstRegS);
    int secondReg = binToDec(secondRegS);
    int thirdReg = binToDec(thirdRegS);

    int shamtInt = binToDec(shamt);
    int immInt = binToDec(imm);
    int addrInt = binToDec(addr);

    mem_register reg1 = firstReg;
    mem_register reg2 = secondReg;
    mem_register reg3 = thirdReg;

    char *ADD = (char *)malloc(sizeof(char) * 5);
    char *SUB = (char *)malloc(sizeof(char) * 5);
    char *MUL = (char *)malloc(sizeof(char) * 5);
    char *MOVI = (char *)malloc(sizeof(char) * 5);
    char *JEQ = (char *)malloc(sizeof(char) * 5);
    char *AND = (char *)malloc(sizeof(char) * 5);
    char *XORI = (char *)malloc(sizeof(char) * 5);
    char *JMP = (char *)malloc(sizeof(char) * 5);
    char *LSL = (char *)malloc(sizeof(char) * 5);
    char *LSR = (char *)malloc(sizeof(char) * 5);
    char *MOVR = (char *)malloc(sizeof(char) * 5);
    char *MOVM = (char *)malloc(sizeof(char) * 5);
    get_config("ADD", ADD, NULL);
    get_config("SUB", SUB, NULL);
    get_config("MUL", MUL, NULL);
    get_config("MOVI", MOVI, NULL);
    get_config("JEQ", JEQ, NULL);
    get_config("AND", AND, NULL);
    get_config("XORI", XORI, NULL);
    get_config("JMP", JMP, NULL);
    get_config("LSL", LSL, NULL);
    get_config("LSR", LSR, NULL);
    get_config("MOVR", MOVR, NULL);
    get_config("MOVM", MOVM, NULL);

    int ADDInt = binToDec(ADD);
    int SUBInt = binToDec(SUB);
    int MULInt = binToDec(MUL);
    int MOVIInt = binToDec(MOVI);
    int JEQInt = binToDec(JEQ);
    int ANDInt = binToDec(AND);
    int XORIInt = binToDec(XORI);
    int JMPInt = binToDec(JMP);
    int LSLInt = binToDec(LSL);
    int LSRInt = binToDec(LSR);
    int MOVRInt = binToDec(MOVR);
    int MOVMInt = binToDec(MOVM);
    free(ADD);
    free(SUB);
    free(MUL);
    free(MOVI);
    free(JEQ);
    free(AND);
    free(XORI);
    free(JMP);
    free(LSL);
    free(LSR);
    free(MOVR);
    free(MOVM);

    if (opCodeInt == ADDInt)
    {
        add(reg1, reg2, reg3);
        info("Executing ADD instruction");
    }
    else if (opCodeInt == SUBInt)
    {
        sub(reg1, reg2, reg3);
        info("Executing SUB instruction");
    }
    else if (opCodeInt == MULInt)
    {
        mul(reg1, reg2, reg3);
        info("Executing MUL instruction");
    }
    else if (opCodeInt == MOVIInt)
    {
        movi(reg1, immInt);
        info("Executing MOVI instruction");
    }
    else if (opCodeInt == JEQInt)
    {
        jeq(reg1, reg2, immInt);
        info("Executing JEQ instruction");
    }
    else if (opCodeInt == ANDInt)
    {
        and(reg1, reg2, reg3);
        info("Executing AND instruction");
    }
    else if (opCodeInt == XORIInt)
    {
        xori(reg1, reg2, immInt);
        info("Executing XORI instruction");
    }
    else if (opCodeInt == JMPInt)
    {
        jmp(addrInt);
        info("Executing JMP instruction");
    }
    else if (opCodeInt == LSLInt)
    {
        lsl(reg1, reg2, shamtInt);
        info("Executing LSL instruction");
    }
    else if (opCodeInt == LSRInt)
    {
        lsr(reg1, reg2, shamtInt);
        info("Executing LSR instruction");
    }
    else if (opCodeInt == MOVRInt)
    {
        movr(reg1, reg2, immInt);
        info("Executing MOVR instruction");
    }
    else if (opCodeInt == MOVMInt)
    {
        movm(reg1, reg2, immInt);
        info("Executing MOVM instruction");
    }
    else
    {
        info("Invalid instruction");
    }

    return 0;
}
