#ifndef PATH_H
#define PATH_H

#include <stddef.h> // For size_t

#ifdef _WIN32
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

void join_paths(char *result, int num_paths, const char *paths[]);

#endif