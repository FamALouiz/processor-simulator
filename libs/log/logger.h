#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include "logger_config.h"

const char *INFO_MESSAGE = "INFO    ";
const char *ERROR_MESSAGE = "ERROR   ";
const char *WARNING_MESSAGE = "WARNING ";

#define warn(message) log_msg(LOG_STATUS_LEVEL_WARNING, message, WARNING_MESSAGE, __FILE__, __LINE__);
#define info(message) log_msg(LOG_STATUS_LEVEL_NORMAL, message, INFO_MESSAGE, __FILE__, __LINE__);
#define error(message) log_msg(LOG_STATUS_LEVEL_ERROR, message, ERROR_MESSAGE, __FILE__, __LINE__);

// Global variables
extern int log_verbosity;
extern int log_output;
extern FILE *log_file;
extern time_t init_time;

// Function declarations
int init_logger(int log_output_code, int log_verbosity_code);
void close_logger();

#endif