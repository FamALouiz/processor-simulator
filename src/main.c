#include "logger.h"

int main(void)
{
    init_logger(LOG_TO_FILE_AND_TERMINAL, LOG_VERBOSITY_DEBUG);
    info("Hello!");
    warn("This is a warning!");
    error("what is the max of  taosidjaoisjdao isjdoiajsd oiajsdio jasoidj aoisjd oaijsdo ijasodi jasoijd oaisjd oiajsoid ");
    close_logger();
}