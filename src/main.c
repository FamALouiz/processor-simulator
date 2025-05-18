#include "logger.h"
#include "mem_manager.h"
#include <stdlib.h>
#include "file_parser.h"

#define TEST_MEMORY_CELLS 5

int main(void)
{
    // Initialize logger for both file and terminal with debug level verbosity
    init_logger(LOG_TO_FILE_AND_TERMINAL, LOG_VERBOSITY_DEBUG);
    info("Processor simulator started");

    // Config and assembly files
    const char *filename = "test.asm";
    const char *properties_filename = "config/InstructionMappings.config";

    // Load instruction configurations and parse assembly file
    load_properties(properties_filename);
    parse_and_encode(filename);

    // Dump first few memory locations
    word *output = (word *)malloc(sizeof(word));
    if (!output)
    {
        error("Memory allocation failed");
        close_logger();
        return 1;
    }

    for (int i = 0; i < TEST_MEMORY_CELLS; i++)
    {
        mem_read(&output, i);
        char message[256];
        snprintf(message, sizeof(message), "Memory at idx %d: 0x%08X", i,
                 ((*output)[0] << 24) | ((*output)[1] << 16) | ((*output)[2] << 8) | (*output)[3]);
        info(message);
    }

    free(output);
    info("Processor simulator completed successfully");
    close_logger();
    return 0;
}