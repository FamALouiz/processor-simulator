#include <stdlib.h>
#include "datapath.h"

#define TEST_MEMORY_CELLS 5

int main(void)
{
    // Initialize logger for both file and terminal with debug level verbosity
    init_logger(LOG_TO_FILE_AND_TERMINAL, LOG_VERBOSITY_DEBUG);
    info("Processor simulator started");

    const char *filename = "test.asm";
    const char *properties_filename = "config/InstructionMappings.config";

    // Load instruction configurations and parse assembly file
    load_properties(properties_filename);
    parse_and_encode(filename);

    initProgramCounter(0);
    pipeline_stage *stages = initializeStages();
    runPipeline(stages);

    info("Processor simulator completed successfully");
    close_logger();
    return 0;
}