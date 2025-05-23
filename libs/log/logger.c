#include "logger_config.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <direct.h> // For Windows mkdir
#include "../util/path.h"

int log_verbosity;
int log_output;
FILE *log_file;
time_t init_time;

const char *TERMINAL_LOG_TEMPLATE_DEBUG = "[%6.2fs] (%s:%d) %s%s - %s\033[0m\n";
const char *FILE_LOG_TEMPLATE_DEBUG = "[%6.2fs] (%s:%d) %s\n";
const char *TERMINAL_LOG_TEMPLATE_INFO = "[%6.2fs] %s%s - %s\033[0m\n";
const char *FILE_LOG_TEMPLATE_INFO = "[%6.2fs] %s\n";

const char *ERROR_COLOR = "\033[1;31m";
const char *WARN_COLOR = "\033[38;5;214m";
const char *DEFAULT_COLOR = "\033[0m";
const char *REGISTER_FILE_TABLE_COLOR = "\033[1;32m";

const char *INFO_MESSAGE = "INFO    ";
const char *ERROR_MESSAGE = "ERROR   ";
const char *WARNING_MESSAGE = "WARNING ";
const char *REGISTER_FILE_MESSAGE = "RF      ";

int init_logger(int log_output_code, int log_verbosity_code)
{
    log_output = log_output_code;
    log_verbosity = log_verbosity_code;
    init_time = time(NULL);

    if (log_output == LOG_TO_FILE_ONLY || log_output == LOG_TO_FILE_AND_TERMINAL)
    {
        char date[20];
        struct tm *t = localtime(&init_time);
        strftime(date, sizeof(date), "%Y-%m-%d_%H:%M", t);

        char file_path[256] = "";
        const char *paths[] = {"logs", date};
        join_paths(file_path, 2, paths);

        log_file = fopen(file_path, "w");
        if (!log_file)
        {
            printf("Failed to open log file: %s\n", file_path);
            return 1;
        }
    }
    return 0;
}

void log_msg(int status_level, char *log_message, const char *file_path, int line)
{
    const char *color;
    const char *type_message;
    switch (status_level)
    {
    case LOG_STATUS_LEVEL_ERROR:
        color = ERROR_COLOR; // Red
        type_message = ERROR_MESSAGE;
        break;
    case LOG_STATUS_LEVEL_WARNING:
        color = WARN_COLOR; // Yellow
        type_message = WARNING_MESSAGE;
        break;
    case LOG_STATUS_LEVEL_RF:
        color = REGISTER_FILE_TABLE_COLOR; // Green
        type_message = REGISTER_FILE_MESSAGE;
        break;
    case LOG_STATUS_LEVEL_NORMAL:
    default:
        color = DEFAULT_COLOR; // Default
        type_message = INFO_MESSAGE;
        break;
    }

    const char *last_file_in_path = get_last_file_in_path(file_path);

    char log_entry[512];
    struct timespec ts_now;
    timespec_get(&ts_now, TIME_UTC);
    double time_diff = (ts_now.tv_sec - init_time) + ts_now.tv_nsec / 1e9;

    switch (log_verbosity)
    {
    case LOG_VERBOSITY_DEBUG:
        snprintf(log_entry, sizeof(log_entry), TERMINAL_LOG_TEMPLATE_DEBUG, time_diff, last_file_in_path, line, color, type_message, log_message);
        break;
    case LOG_VERBOSITY_INFO:
    default:
        snprintf(log_entry, sizeof(log_entry), TERMINAL_LOG_TEMPLATE_INFO, time_diff, color, type_message, log_message);
    }

    if (log_output == LOG_TO_TERMINAL_ONLY || log_output == LOG_TO_FILE_AND_TERMINAL)
    {
        printf("%s", log_entry);
    }

    if (log_output == LOG_TO_FILE_ONLY || log_output == LOG_TO_FILE_AND_TERMINAL)
    {
        if (log_file)
        {
            switch (log_verbosity)
            {
            case LOG_VERBOSITY_DEBUG:
                fprintf(log_file, FILE_LOG_TEMPLATE_DEBUG, time_diff, last_file_in_path, line, type_message, log_message);
                break;
            case LOG_VERBOSITY_INFO:
            default:
                fprintf(log_file, FILE_LOG_TEMPLATE_INFO, time_diff, type_message, log_message);
            }
            fflush(log_file);
        }
    }
}

void close_logger()
{
    if (log_file)
    {
        fclose(log_file);
        log_file = NULL;
    }
}