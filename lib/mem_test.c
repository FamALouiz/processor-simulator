#include "../include/mem_manager.h"
#include <stdio.h>

int main()
{
 word myword = "fnd";
 word myword2 = "lnd";
 mem_write(&myword, 1025);
 reg_write(R12,&myword2);

 word zero = "0000";
 word* output = &zero;


 mem_read(output, 1025);

 word* output2 = &zero;
 reg_read(R12,output2);

 printf("%s", output);
}