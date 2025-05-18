#include "include/file_parser/file_parser.h"

//main memory
static memory_interface main_memory;
//Data path skeleton
static int cycles =0;

//Increments Cycle
void nextCycle(int* cycles);
int getCycle(int* cycles);

//Functions relating to program counter
void initProgramCounter(unsigned int start);
void updateProgramCounter();

//define pipeline stage
typedef void(*pipeline_stage_action)();
typedef struct 
{
    unsigned int duration;
    pipeline_stage_action action;
} pipeline_stage;

//pipeline is an array of pipeline_stages
static pipeline_stage* stages;

//create your own pipeline
pipeline_stage* initializeStages();

inline int calculateCycleCount(unsigned int ins_count); 
void runPipeline(pipeline_stage* pipeline,unsigned int instruction_count);

