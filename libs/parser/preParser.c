#include <stdio.h>
#include <mem_manager.h>
#include <word.h>
#include <logger.h>

void preParse(word* word){//this is for iterating over the word to convert it to bits
    int res = 0;
    char binaryS[32];
    for(int j=0;j<4;j++){
        for(int i = 0;i<8;i++){
            res = (int) word[i] & (1 << i);
            if(res == 0){
                binaryS[j*8+i] = '0';

            }else if(res == 1){
                binaryS[j*8+i] = '1';
            }
        }
    }
    
}