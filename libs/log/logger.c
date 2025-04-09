#include "logger_config.h"
#include <stdio.h>
#include <time.h>
#include "../util/path.h"

int log_verbosity;
int log_output;
FILE *log_file;
time_t init_time;

const char *TERMINAL_LOG_TEMPLATE = "[%6.2fs] (%s:%d) %s - %s%s\033[0m\n";
const char *FILE_LOG_TEMPLATE = "[%6.2fs] (%s:%d) %s\n";

const char *ERROR_COLOR = "\033[1;31m";
const char *WARN_COLOR = " \033[1;33m";
const char *DEFAULT_COLOR = "\033[0m";

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

void log_msg(int status_level, char *log_message, char *type_message, const char *file_path, int line)
{

    const char *color;
    switch (status_level)
    {
    case LOG_STATUS_LEVEL_ERROR:
        color = ERROR_COLOR; // Red
        break;
    case LOG_STATUS_LEVEL_WARNING:
        color = WARN_COLOR; // Yellow
        break;
    case LOG_STATUS_LEVEL_NORMAL:
    default:
        color = DEFAULT_COLOR; // Default
        break;
    }

    const char *last_file_in_path = get_last_file_in_path(file_path);

    char log_entry[512];
    time_t current_time = time(NULL);
    double time_diff = difftime(current_time, init_time);
    snprintf(log_entry, sizeof(log_entry), TERMINAL_LOG_TEMPLATE, time_diff, last_file_in_path, line, type_message, color, log_message);

    if (log_output == LOG_TO_TERMINAL_ONLY || log_output == LOG_TO_FILE_AND_TERMINAL)
    {
        printf("%s", log_entry);
    }

    if (log_output == LOG_TO_FILE_ONLY || log_output == LOG_TO_FILE_AND_TERMINAL)
    {
        if (log_file)
        {
            fprintf(log_file, FILE_LOG_TEMPLATE, time_diff, last_file_in_path, line, type_message, log_message);
            fflush(log_file);
        }
    }
}

void close_logger()
{
    free(log_file);
}