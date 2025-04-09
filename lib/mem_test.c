#include "../include/mem_manager.h"
#include <stdio.h>

int main()
{
 word myword = "fnd";
 mem_write(&myword, 1025);
 
 word* output;
 mem_read(output, 1025);
 printf("%s", output);
}