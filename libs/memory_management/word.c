#include "include/memory_management/word.h"

//CONVERSIONS
void word_to_int(const word* w, unsigned int* i)
{
    *i = ((*w)[0] << 24) | ((*w)[1] << 16) | ((*w)[2] << 8 )| ((*w)[3] << 0); 
}

void int_to_word(unsigned int i, word* w)
{
    (*w)[0] = (i >> 24) & 255;
    (*w)[1] = (i >> 16) & 255;
    (*w)[2] = (i >> 8) & 255;
    (*w)[3] = (i >> 0) & 255;
}