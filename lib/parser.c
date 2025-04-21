#include <stdio.h>
#include <mem_manager.h>
#include <word.h>

void ADD(mem_register reg1, mem_register reg2,mem_register reg3){
    word* contentR2;
    word* contentR3;
    reg_read(reg2,contentR2);
    reg_read(reg3, contentR3);
    //word* res = contentR2+contentR3;
    //reg_write(reg1, res);
}
void SUB(mem_register reg1, mem_register reg2,mem_register reg3){
    word* contentR2;
    word* contentR3;
    reg_read(reg2,contentR2);
    reg_read(reg3, contentR3);
}
void MUL(mem_register reg1, mem_register reg2,mem_register reg3){
    word* contentR2;
    word* contentR3;
    reg_read(reg2,contentR2);
    reg_read(reg3, contentR3);
}
void MOVI(mem_register reg1, word* imm){
    reg_write(reg1, imm);
}
void JEQ(mem_register reg1,mem_register reg2, word* imm ){
    


}

mem_register getReg(int Rnumber){//to get the actual register from its number
    mem_register allregister[31]={R1, R2, R3, R4, R5, R6,
                                R7, R8, R9, R10, R11, R12,
                                R13, R14, R15, R16, R17, R18,
                                R19, R20, R21, R22, R23, R24,
                                R25, R26, R27, R28, R29, R30, R31};
    return allregister[Rnumber];
}

int binToDec(int bin){//to convert binary numbers to int to be able to deal with them easily
    int res = 0;
    int exponent = 1;
    int rightBit;
    
    while (bin != 0){
        rightBit = bin%10;
        res = res+(rightBit*exponent);
        bin = bin/10;
        exponent = exponent*2;
    }

    return res;
}
int main(){
    char inst[] = "";//the instruction
    scanf("%s", inst);
    char opCode[4];
    for (int i = 0; i < 4; i++){//to get the first 4 bits of each binary instruction
        opCode[i] = inst[i];
    }
    int opCodeInt = binToDec(atoi(opCode));//converts the 4 bits from string to int and then to decimal

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
    int firstReg = binToDec(atoi(firstRegS));
    int secondReg = binToDec(atoi(secondRegS));
    int thirdReg = binToDec(atoi(thirdRegS));

    mem_register reg1 = getReg(firstReg);
    mem_register reg2 = getReg(secondReg);
    mem_register reg3 = getReg(thirdReg);

    switch (opCodeInt) //all cases can be replaced with actual functions later to do the actual functionality
    {
        case 0:
           printf("ADD, type R");
           ADD(reg1, reg2, reg3); 
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


