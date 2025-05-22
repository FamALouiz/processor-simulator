#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "word.h"
#include "logger.h"
#include "mem_manager.h"
#include "functions.h"

char *preParse(word *word);

int binToDec(char bin[]);

int parse(word *word);