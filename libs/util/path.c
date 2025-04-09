#include <stdio.h>
#include <string.h>
#include "path.h"

void join_paths(char *result, int num_paths, const char *paths[])
{
    result[0] = '\0'; // Initialize result as an empty string

    for (int i = 0; i < num_paths; i++)
    {
        if (i > 0)
        {
            size_t len = strlen(result);
            if (len > 0 && result[len - 1] != PATH_SEPARATOR[0])
            {
                strcat(result, PATH_SEPARATOR);
            }
        }
        strcat(result, paths[i]);
    }
}