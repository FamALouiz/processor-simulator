#include "logger.h"
#include "mem_manager.h"
#include <stdlib.h>
#include "file_parser.h"

int main(void)
{
    init_logger(LOG_TO_FILE_AND_TERMINAL, LOG_VERBOSITY_DEBUG);
    info("Hello!");
    warn("This is a warning!");
    error("what is the max of  taosidjaoisjdao isjdoiajsd oiajsdio jasoidj aoisjd oaijsdo ijasodi jasoijd oaisjd oiajsoid ");

    char *filename = "test.asm";
    char *properties_filename = "config/InstructionMappings.config";
    load_properties(properties_filename);
    parse_and_encode(filename);

    word *output = (word *)malloc(sizeof(word));

    for (int i = 0; i < 5; i++)
    {
        mem_read(&output, i);
        char message[256];
        snprintf(message, sizeof(message), "Memory at idx %d: 0x%08X", i, *output);
        info(message);
    }

    free(output);

    close_logger();
}