#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include "logger_config.h"

// Global variables
extern int log_verbosity;
extern int log_output;
extern FILE *log_file;
extern time_t init_time;

// Function declarations
int init_logger(int log_output_code, int log_verbosity_code);
void warn(const char *message);
void info(const char *message);
void error(const char *message);
void close_logger();

#endif