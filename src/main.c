#include <stdlib.h>
#include "datapath.h"

int main(void)
{
    init_logger(LOG_TO_FILE_AND_TERMINAL, LOG_VERBOSITY_DEBUG);

    incrementProgramCounter();
    pipeline_stage* stages = initializeStages();
    runPipeline(stages);
    close_logger();
}