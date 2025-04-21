#include "logger.h"
#include "mem_manager.h"
#include <stdlib.h>

int main(void)
{
    init_logger(LOG_TO_FILE_AND_TERMINAL, LOG_VERBOSITY_DEBUG);
    info("Hello!");
    warn("This is a warning!");
    error("what is the max of  taosidjaoisjdao isjdoiajsd oiajsdio jasoidj aoisjd oaijsdo ijasodi jasoijd oaisjd oiajsoid ");

    word input = "add";
    mem_write(&input, -1);
    word *output = (word *)malloc(sizeof(word));
    mem_read(output, 10);

    close_logger();

    printf("test");
}