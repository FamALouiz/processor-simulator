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
    parse_and_encode(filename);

    word *instructions = (word *)malloc(sizeof(word) * 100); // adjust size as needed
    for (int i = 0; i < 100; i++)
    {
        mem_read(&instructions[i], i);
        char message[] = "Instruction at address %d: %s";
        scanf_s(&message, i, instructions[i]);
        info(message);
    }
    free(instructions);

    close_logger();
}