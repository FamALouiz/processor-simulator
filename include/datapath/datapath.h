#ifndef DATA_PATH_H
#define DATA_PATH_H

#include "file_parser.h"
#include "logger.h"
#include "word.h"
#include <string.h>

// number of stages in pipeline
#define STAGES_NUMBER 5
// main memory
static memory_interface main_memory;
// Data path skeleton
static int cycles = 0;

// Increments Cycle
void nextCycle(int *cycles);
int getCycle(int *cycles);

// Functions relating to program counter
void initProgramCounter(unsigned int start);
void incrementProgramCounter();

// define pipeline stage
typedef struct pipeline_stage pipeline_stage;
typedef int (*pipeline_stage_action)(pipeline_stage *);

struct pipeline_stage
{
    int isReadyNextCycle;
    int isReadyCurrentCycle;
    unsigned int duration;
    unsigned int elapsed;
    const char *log_info;

    pipeline_stage_action action;
};

// create your own pipeline
pipeline_stage *initializeStages();

void runPipeline(pipeline_stage *pipeline);

int instructionFetchAction(pipeline_stage *stages);
int instructionDecodeAction(pipeline_stage *stages);
int executeAction(pipeline_stage *stages);
int memAction(pipeline_stage *stages);
int writeBackAction(pipeline_stage *stages);

#endif