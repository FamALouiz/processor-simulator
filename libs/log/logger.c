#include "logger_config.h"
#include <stdio.h>
#include <time.h>
#include "../util/path.h"

int log_verbosity;
int log_output;
FILE *log_file;
time_t init_time;

int init_logger(int log_output_code, int log_verbosity_code)
{
    log_output = log_output_code;
    log_verbosity = log_verbosity_code;

    if (log_output == LOG_TO_FILE_ONLY || log_output == LOG_TO_FILE_AND_TERMINAL)
    {
        char date[20];
        init_time = time(NULL);
        struct tm *t = localtime(&init_time);
        strftime(date, sizeof(date), "%Y-%m-%d_%H:%M", t);

        char *file_path = "";
        const char *paths[] = {"logs", date};
        join_paths(file_path, 2, paths);

        log_file = fopen(file_path, "w");
    }
    return 0;
}

void close_logger()
{
    free(log_file);
}
int log_msg(int status_level, char *log_message)
{
}

void warn(const char *message)
{
    log_msg(LOG_STATUS_LEVEL_WARNING, message);
}
void info(const char *message) {}
void error(const char *message) {}