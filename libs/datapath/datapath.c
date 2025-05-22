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

    //Set default values to 0
    pipeline_write(RIF, default_word);
    pipeline_write(RID, default_word);
    pipeline_write(REX, default_word);
    pipeline_write(RMEM, default_word);
    pipeline_write(RWB, default_word);

    return stages;
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
            if (pipeline[i].isReadyCurrentCycle >0)
            {
                info(pipeline[i].log_info);
                pipeline[i].isReadyNextCycle--;
                pipeline[i].elapsed++;
                if (pipeline[i].elapsed == pipeline[i].duration)
                {
                    pipeline[i].elapsed = 0;
                        if (pipeline[i].action(pipeline))
                        {
                            displayRegisterFile();
                            return;
                        }
                    
                }

            }
        }
        
        nextCycle(&cycles);

        char msg[100];
        sprintf(msg, "CYCLE NUMBER: %d \n", getCycle(&cycles));
        info(msg);

        if( (getCycle(&cycles) % 2) == 0 && (getCycle(&cycles) < 14))
        {
            pipeline[0].isReadyNextCycle = 1;
        }else{
            pipeline[0].isReadyNextCycle = 0;
        }

        for(int i = 0; i < 5e8; i++){
        }
    }
}

int instructionFetchAction(pipeline_stage *stages)
{
    //get previous value, move it to the next instruction
    word* rif_word = (word*)malloc(sizeof(word));
    pipeline_read(RIF, rif_word);

    if( !(rif_word[0] == 0 &&rif_word[1] == 0 &&rif_word[2] == 0 &&rif_word[3] == 0) )
    {
        //move to next register
        pipeline_write(RID, rif_word);
    }

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

    //Increment PC
    incrementProgramCounter();

    // Enable next register in the next clock cycle for 2 clock cycles
    stages[1].isReadyNextCycle += stages[1].duration; 
    return 0;
}

int instructionDecodeAction(pipeline_stage *stages)
{   
    //get previous value, move it to the next instruction
    word* rid_word = (word*)malloc(sizeof(word));
    pipeline_read(RID, rid_word);

    if( !(rid_word[0] == 0 &&rid_word[1] == 0 &&rid_word[2] == 0 &&rid_word[3] == 0) )
    {
        //move to next register
        pipeline_write(REX, rid_word);
    }

    //Enable next stage
    stages[2].isReadyNextCycle += stages[2].duration;
    return 0;
}

int executeAction(pipeline_stage *stages)
{
    //get previous value, move it to the next instruction
    word* rex_word = (word*)malloc(sizeof(word));
    pipeline_read(REX, rex_word);

    if( !(rex_word[0] == 0 &&rex_word[1] == 0 &&rex_word[2] == 0 &&rex_word[3] == 0) )
    {
        //move to next register
        pipeline_write(RMEM, rex_word);
    }

    //read instruction
    word* instruction = (word*) malloc(sizeof(word));
    pipeline_read(RID, instruction); 

    warn("Read Instruction");
    //run parse function
    int shouldExit = parse(instruction);
    warn("Parsed Instruction");
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