#include "datapath.h"

// Increment cycle
void nextCycle(int *cycles)
{
    (*cycles)++;
}

int getCycle(int *cycles)
{
    return *cycles;
}

// initialize program counter to a particular value
void initProgramCounter(unsigned int start)
{
    word *val = (word *)malloc(sizeof(word));
    int_to_word(start, val);
    reg_write(PC, val);
}

void incrementProgramCounter()
{
    word *pc_word = (word *)malloc(sizeof(word));
    unsigned int pc_int;
    reg_read(PC, pc_word);
    word_to_int(pc_word, &pc_int);
    pc_int++;
    int_to_word(pc_int, pc_word);
    reg_write(PC, pc_word);
}

pipeline_stage *initializeStages()
{
    pipeline_stage *stages = (pipeline_stage *)malloc(sizeof(pipeline_stage) * STAGES_NUMBER); // Pipeline is composed of 5 stages
    // STAGE 1: Instruction Fetch (IF)
    pipeline_stage IF;
    memset(&IF, 0, sizeof(pipeline_stage));
    IF.isReadyNextCycle = 1;
    IF.duration = 1;
    IF.log_info = "INSTRUCTION FETCH";
    IF.action = &instructionFetchAction;

    // STAGE 2: Instruction Decode (ID)
    pipeline_stage ID;
    memset(&ID, 0, sizeof(pipeline_stage));
    ID.isReadyNextCycle = 0;
    ID.duration = 2;
    ID.log_info = "INSTRUCTION DECODE";
    ID.action = &instructionDecodeAction;

    // STAGE 3: Execute (EX)
    pipeline_stage EX;
    memset(&EX, 0, sizeof(pipeline_stage));
    EX.isReadyNextCycle = 0;
    EX.duration = 2;
    EX.log_info = "EXECUTING INSTRUCTION";
    EX.action = &executeAction;

    // STAGE 4: Memory (MEM)
    pipeline_stage MEM;
    memset(&MEM, 0, sizeof(pipeline_stage));
    MEM.isReadyNextCycle = 0;
    MEM.duration = 1;
    MEM.log_info = "MEMORY ACCESS";
    MEM.action = &memAction;

    // STAGE 5: Write Back (WB)
    pipeline_stage WB;
    memset(&WB, 0, sizeof(pipeline_stage));
    WB.isReadyNextCycle = 0;
    WB.duration = 1;
    WB.log_info = "WRITING BACK";
    WB.action = &writeBackAction;

    stages[0] = IF;
    stages[1] = ID;
    stages[2] = EX;
    stages[3] = MEM;
    stages[4] = WB;

    //memset all register to default values
    word* default_word = (word*)malloc(sizeof(word));
    //set this word to a default value of 0
    reg_read(R0, default_word);

    unsigned int def;
    word_to_int(default_word,&def);
    char ms[1024];
    sprintf(ms, "DEFAULT_WORD: %d",def);
    //rf(ms);

    //Set default values to 0
    pipeline_write(RIF, default_word);
    pipeline_write(RID, default_word);
    pipeline_write(REX, default_word);
    pipeline_write(RMEM, default_word);
    pipeline_write(RWB, default_word);

    

    return stages;
}

void printAllPipelineRegisters()
{
    word *if_word = (word *)malloc(sizeof(word));
    word *id_word = (word *)malloc(sizeof(word));
    word *ex_word = (word *)malloc(sizeof(word));
    word *mem_word = (word *)malloc(sizeof(word));
    word *wb_word = (word *)malloc(sizeof(word));

    pipeline_read(RIF, if_word);
    pipeline_read(RID, id_word);
    pipeline_read(REX, ex_word);
    pipeline_read(RMEM, mem_word);
    pipeline_read(RWB, wb_word);

    unsigned int if_int;
    unsigned int id_int;
    unsigned int ex_int;
    unsigned int mem_int;
    unsigned int wb_int;

    word_to_int(if_word, &if_int);
    word_to_int(id_word, &id_int);
    word_to_int(ex_word, &ex_int);
    word_to_int(mem_word, &mem_int);
    word_to_int(mem_word, &wb_int);
    
    char msg[1024];
    sprintf(msg, "LOOP <> IF: %d, ID: %d, EX: %d, MEM: %d, WB: %d",
    if_int, id_int, ex_int, mem_int, wb_int);
    rf(msg);
}
void runPipeline(pipeline_stage *pipeline, char** buffer)
{
    
        pipeline[0].isReadyCurrentCycle = pipeline[0].isReadyNextCycle;
        pipeline[1].isReadyCurrentCycle = pipeline[1].isReadyNextCycle;
        pipeline[2].isReadyCurrentCycle = pipeline[2].isReadyNextCycle;
        pipeline[3].isReadyCurrentCycle = pipeline[3].isReadyNextCycle;
        pipeline[4].isReadyCurrentCycle = pipeline[4].isReadyNextCycle;

        *buffer = (char*)malloc(sizeof(char) * 1024);
        (*buffer)[0] = '\0';
        for (unsigned int i = 0; i < STAGES_NUMBER; i++)
        {
            if (pipeline[i].isReadyCurrentCycle >0)
            {
                char buff[1024];
                sprintf(buff, "FROM CLI: %s\n", pipeline[i].log_info);
                strcat(*buffer,buff);

                pipeline[i].isReadyNextCycle--;
                pipeline[i].elapsed++;
                if (pipeline[i].elapsed == pipeline[i].duration)
                {
                    pipeline[i].elapsed = 0;
                        if (pipeline[i].action(pipeline))
                        {
                            //displayRegisterFile();
                            return;
                        }
                    
                }

            }
        }
        
        nextCycle(&cycles);
        char cycleMSG[100];
        sprintf(cycleMSG, "\n CYCLE NUMBER: %d \n ---------------------- \n", getCycle(&cycles));

        strcat(*buffer, cycleMSG);
        //info(cycleMSG);

        if( (getCycle(&cycles) % 2) == 0 )
        {
            pipeline[0].isReadyNextCycle = 1;
        }else{
            pipeline[0].isReadyNextCycle = 0;
        }

        
        //printAllPipelineRegisters();

        for(int i = 0; i < 8e8; i++){
        }
    
}

int instructionFetchAction(pipeline_stage *stages)
{
    
    // Get Current PC
    word *pc_word = (word *)malloc(sizeof(word));
    reg_read(PC, pc_word);
    unsigned int pc_int;
    word_to_int(pc_word, &pc_int);
    // Fetch instruction in this PC and put it inside its own register
    // For use by instruction decoder (like IR register)
    word *instruction = (word *)malloc(sizeof(word));
    mem_read(instruction, pc_int);
    
    
    // Write into pipeline register 
    word* prevInstruction = (word*)malloc(sizeof(word));
    pipeline_read(RIF, prevInstruction);

    unsigned int a;
    word_to_int(prevInstruction, &a);
    if( !(a == 0))
    {
        //There is a previous instruction, move the current to the next one
        pipeline_write(RID, prevInstruction);
    } 
    
    word *if_word = (word *)malloc(sizeof(word));
    pipeline_write(RIF, instruction);
    
    //Increment PC
    incrementProgramCounter();

    // Enable next register in the next clock cycle for 2 clock cycles
    stages[1].isReadyNextCycle += stages[1].duration; 



    // // Convert the word to an integer for easier bit manipulation
    // unsigned int instruction_int;
    // word_to_int(instruction, &instruction_int);

    // // Extract opcode (bits 31-28)
    // int opCodeInt = (instruction_int >> 28) & 0xF;

    // int ENDInt = 0xF;
    // if (opCodeInt == ENDInt)
    // {
    //     return 1;
    // }

    return 0;
}

int instructionDecodeAction(pipeline_stage *stages)
{   

    word* currentInstruction = (word*)malloc(sizeof(word));

    pipeline_read(REX, currentInstruction);
   
    unsigned int a;
    word_to_int(currentInstruction, &a);
   
    if(a == 0 || a == 0xFFFFFF00)
    {
        pipeline_read(RID, currentInstruction);
        pipeline_write(REX, currentInstruction);
    }
    
    //Enable next stage
    stages[2].isReadyNextCycle += stages[2].duration;
    return 0;
}

int executeAction(pipeline_stage *stages)
{
    //read instruction
    word* instruction = (word*) malloc(sizeof(word));
    pipeline_read(REX, instruction); 

    unsigned int test_value;
    word_to_int(instruction, &test_value);

    if(test_value == 0xFFFFFF00)
    {
        stages[3].isReadyNextCycle += stages[3].duration;
        return 0;
    }
    //run parse function
    int shouldExit = parse(instruction);
    warn("Parsed Instruction");

    word* zero = (word*)malloc(sizeof(word));
    reg_read(R0, zero);
    pipeline_write(REX, zero);

    if(return_interrupt() == 1)
    {
        warn("INTERRUPT");
        //RESET ALLLLLLLL
        //memset all register to default values
        word* default_word = (word*)malloc(sizeof(word));
        //set this word to a default value of 0
        int value = 0xFFFFFF00;
        int_to_word(value, default_word);
        //Set default values to 0
        pipeline_write(RIF, default_word);
        pipeline_write(RID, default_word);
        pipeline_write(REX, default_word);
        pipeline_write(RMEM, default_word);
        pipeline_write(RWB, default_word);


        //Fetch instruction
        // Get Current PC
        word *pc_word = (word *)malloc(sizeof(word));
        reg_read(PC, pc_word);
        unsigned int pc_int;
        word_to_int(pc_word, &pc_int);
        // Fetch instruction in this PC and put it inside its own register
        // For use by instruction decoder (like IR register)
        word *instruction = (word *)malloc(sizeof(word));
        mem_read(instruction, pc_int);
        pipeline_write(RIF, instruction);

        //Increment PC
        incrementProgramCounter();


        //release interrupt
        release_interrupt();
    }
    pipeline_read(RID, instruction);
    pipeline_write(REX, instruction);


    stages[3].isReadyNextCycle += stages[3].duration;
    return shouldExit;
}

int memAction(pipeline_stage *stages)
{
    stages[4].isReadyNextCycle += stages[4].duration;   
    return 0;
}
int writeBackAction(pipeline_stage *stages)
{

    return 0;
}
void displayRegisterFile()
{
    rf("Entered Display");
    //We need to display the content of all registers
    word* current = (word*)malloc(sizeof(word));
    unsigned int current_int;
    for(unsigned int i =0; i < (R0 + 1);i++)
    {
        reg_read(i, current);
        word_to_int(current, &current_int);
        char msg[1024];
        sprintf(msg, "REGISTER R%d: %d", (i+1), current_int);

        //print msg
        rf(msg);
    }
}