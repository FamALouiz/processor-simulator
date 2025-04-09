#include "logger.h"

int main(void)
{
    init_logger(LOG_TO_FILE_ONLY, LOG_VERBOSITY_INFO);
    close_logger();
}