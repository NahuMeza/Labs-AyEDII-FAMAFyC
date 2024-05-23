#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "strfuncs.h"

size_t string_length(const char *str){
    size_t res = 0;
    for(unsigned int i = 0; str[i] != '\0'; i++){
        res++;
    }
    return res;
}

char *string_filter(const char *str, char c){
    char *strc = NULL;
    strc = malloc(string_length(str)*sizeof(char));
    unsigned int strc_pos = 0;
    for(unsigned int i = 0; str[i] != '\0'; i++){
        if(str[i] != c){
            strc[strc_pos] = str[i];
            strc_pos++;
        }
    }
    return strc;
}

bool string_is_symmetric(const char *str){
    bool sym = true;
    size_t length = string_length(str);
    for(unsigned int i = 0; i < length - i; i++){
        sym = sym && str[i] == str[length - i - 1];
    }
    return sym;
}