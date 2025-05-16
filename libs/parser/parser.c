#include <stdio.h>
#include <stdlib.h>  
#include <string.h> 
#include <mem_manager.h>
#include <word.h>
#include <logger.h>

int binToDec(char bin[]){//to convert binary numbers to int to be able to deal with them easily
    int res = 0;
    int exponent = 1;
    int length = sizeof(bin)/sizeof(bin[0]);
    for (int i = 0; i < length; i++){
        if (i==length-1){//if the loop is at the last bit of the binary number string
            res = res + atoi(bin[0])*exponent;
        }else{
            res = res + atoi(bin[0])*exponent;
            exponent = exponent*2;
            stnscpy(bin, i+1, length-1);//to remove the firtst bit fromm the binary number string
            int lenofBin = sizeof(bin)/sizeof(bin[0]);
            bin[lenofBin-1] = '\0';//making sure the string is terminated, because idk if stnscpy terminates it or not
        }
    }
    return res;
}
void parse(word* word){
    char inst[32] = preParse(word);
    char opCode[4];

    for (int i = 0; i < 4; i++){//to get the first 4 bits of each binary instruction
        opCode[i] = inst[i];
    }
    int opCodeInt = binToDec(opCode);//converts the 4 bits from string to int and then to decimal

    char format;//(NOT NECCESSARY)can be used in switch or if in order to know how to translate each instruction

    char firstRegS[5];
    char secondRegS[5];
    char thirdRegS[5];//in case of R type

    for (int i=4;i<9;i++){//get the binary representation of the first register
        firstRegS[i-4] = inst[i];
    }
    for (int i = 9;i<14;i++){//get the binary representation of the second register
        secondRegS[i-9] = inst[i];
    }
    for (int i = 14;i<19;i++){//get the binary representation of the third register
        thirdRegS[i-9] = inst[i];
    }
    int firstReg = binToDec(firstRegS);
    int secondReg = binToDec(secondRegS);
    int thirdReg = binToDec(thirdRegS);

    mem_register reg1 = firstReg;
    mem_register reg2 = secondReg;
    mem_register reg3 = thirdReg;

    switch (opCodeInt) //all cases can be replaced with actual functions later to do the actual functionality
    {
        case 0:
           printf("ADD, type R");
           //ADD(reg1, reg2, reg3); 
           format = 'R';
           break;
        case 1:
            printf("SUB, type R");
            format = 'R';
            break;
        case 2:
            printf("MUL, type R");
            format = 'R';
            break;
        case 3:
            printf("MOVI, type I");
            format = 'I';
            break;
        case 4:
            printf("JEQ, type I");
            format = 'I';
            break;
        case 5:
            printf("AND, type R");
            format = 'R';
            break;
        case 6:
            printf("XORI, type I");
            format = 'I';
            break;
        case 7:
            printf("JMP, type J");
            format = 'J';
            break;
        case 8:
            printf("LSL, type R");
            format = 'R';
            break;
        case 9:
            printf("LSR, type R");
            format = 'R';
            break;
        case 10:
            printf("MOVR, type I");
            format = 'I';
            break;
        case 11:
            printf("MOVM, type I");
            format = 'I';
            break;
    default:
        break;
    }

    printf("hello world!");

return 0;

}


