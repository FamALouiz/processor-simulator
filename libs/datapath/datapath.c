#include "include/datapath/datapath.h"

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
    pipeline_stage *stages = (pipeline_stage *)malloc(sizeof(pipeline_stage) * STAGES_NUMBER);

    // Pipeline is composed of 5 stages
    // STAGE 1: Instruction Fetch (IF)
    pipeline_stage IF = {0};
    IF.isReadyNextCycle = 1;
    IF.duration = 1;
    IF.log_info = "INSTRUCTION FETCH";
    IF.action = NULL;

    // STAGE 2: Instruction Decode (ID)
    pipeline_stage ID = {0};
    ID.isReadyNextCycle = 0;
    ID.duration = 2;
    ID.log_info = "INSTRUCTION DECODE";
    ID.action = NULL;

    // STAGE 3: Execute (EX)
    pipeline_stage EX = {0};
    EX.isReadyNextCycle = 0;
    EX.duration = 2;
    EX.log_info = "EXECUTING INSTRUCTION";
    EX.action = NULL;

    // STAGE 4: Memory (MEM)
    pipeline_stage MEM = {0};
    MEM.isReadyNextCycle = 0;
    MEM.duration = 1;
    MEM.log_info = "MEMORY ACCESS";
    MEM.action = NULL;

    // STAGE 5: Write Back (WB)
    pipeline_stage WB = {0};
    WB.isReadyNextCycle = 0;
    WB.duration = 1;
    WB.log_info = "WRITING BACK";
    WB.action = NULL;

    stages[0] = IF;
    stages[1] = ID;
    stages[2] = EX;
    stages[3] = MEM;
    stages[4] = WB;
}

void runPipeline(pipeline_stage *pipeline)
{
    while (1)
    {
        pipeline[0].isReadyCurrentCycle = pipeline[0].isReadyNextCycle;
        pipeline[1].isReadyCurrentCycle = pipeline[1].isReadyNextCycle;
        pipeline[2].isReadyCurrentCycle = pipeline[2].isReadyNextCycle;
        pipeline[3].isReadyCurrentCycle = pipeline[3].isReadyNextCycle;
        pipeline[4].isReadyCurrentCycle = pipeline[4].isReadyNextCycle;
        for (unsigned int i = 0; i < STAGES_NUMBER; i++)
        {
            pipeline[i].elapsed++;
            if(pipeline[i].elapsed == pipeline[i].duration)
            {
                pipeline[i].elapsed = 0;
                if (pipeline[i].isReadyCurrentCycle)
                    {
                        info(pipeline[i].log_info);
                        if (pipeline[i].action(pipeline))
                        {
                            return;
                        }
                    }
            }
            
        }
        nextCycle(&cycles);
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
    // Write into pipeline register (IR)
    pipeline_write(RIF, instruction);
    // Disable fetching in the next clock cycle
    stages[0].isReadyNextCycle = 0;
    // Enable next register in the next clock cycle
    stages[1].isReadyNextCycle = 1;
    
    //Disable MEM in the same clock cycle, but enable for the next clock cycle
    stages[3].isReadyCurrentCycle = 0;
    stages[3].isReadyNextCycle = 1;
    
    return 0;
}

int instructionDecodeAction(pipeline_stage* stages)
{
    
    return 0;
}