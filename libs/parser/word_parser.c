#include "word_parser.h"

int parse(word *word)
{
    // Convert the word to an integer for easier bit manipulation
    unsigned int instruction_int;
    word_to_int(word, &instruction_int);

    // Extract opcode (bits 31-28)
    int opCodeInt = (instruction_int >> 28) & 0xF;

    // Extract register indices using bit masks and shifts
    // First register (bits 27-23)
    int firstReg = (instruction_int >> 23) & 0x1F;

    // Second register (bits 22-18)
    int secondReg = (instruction_int >> 18) & 0x1F;

    // Third register (bits 17-13)
    int thirdReg = (instruction_int >> 13) & 0x1F;

    // Extract immediate, shift amount and address fields
    // Shift amount for R-type (bits 12-0)
    int shamtInt = instruction_int & 0x1FFF;

    // Immediate value for I-type (bits 17-0)
    int immInt = instruction_int & 0x3FFFF;

    // Address for J-type (bits 27-0)
    int addrInt = instruction_int & 0xFFFFFFF;

    // Map register indices to memory registers
    mem_register reg1 = firstReg;
    mem_register reg2 = secondReg;
    mem_register reg3 = thirdReg;

    char message[256];
    // snprintf(message, sizeof(message), "Instruction: %08X, Opcode: %d, Reg1: %d, Reg2: %d, Reg3: %d, Imm: %d, Shamt: %d, Addr: %d", instruction_int, opCodeInt, reg1, reg2, reg3, immInt, shamtInt, addrInt);
    // warn(message);

    char ADD[5];
    char SUB[5];
    char MUL[5];
    char MOVI[5];
    char JEQ[5];
    char AND[5];
    char XORI[5];
    char JMP[5];
    char LSL[5];
    char LSR[5];
    char MOVR[5];
    char MOVM[5];
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

    snprintf(message, sizeof(message), "ADD: %s, SUB: %s, MUL: %s, MOVI: %s, JEQ: %s, AND: %s, XORI: %s, JMP: %s, LSL: %s, LSR: %s, MOVR: %s, MOVM: %s",
             ADD, SUB, MUL, MOVI, JEQ, AND, XORI, JMP, LSL, LSR, MOVR, MOVM);
    warn(message);

    int ADDInt = (int)strtol(ADD, NULL, 2);
    int SUBInt = (int)strtol(SUB, NULL, 2);
    int MULInt = (int)strtol(MUL, NULL, 2);
    int MOVIInt = (int)strtol(MOVI, NULL, 2);
    int JEQInt = (int)strtol(JEQ, NULL, 2);
    int ANDInt = (int)strtol(AND, NULL, 2);
    int XORIInt = (int)strtol(XORI, NULL, 2);
    int JMPInt = (int)strtol(JMP, NULL, 2);
    int LSLInt = (int)strtol(LSL, NULL, 2);
    int LSRInt = (int)strtol(LSR, NULL, 2);
    int MOVRInt = (int)strtol(MOVR, NULL, 2);
    int MOVMInt = (int)strtol(MOVM, NULL, 2);
    int ENDInt = 0xFFFFFFFF;

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

    if (opCodeInt == ENDInt)
    {
        return 1;
    }

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
