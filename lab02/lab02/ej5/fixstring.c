#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"


unsigned int fstring_length(fixstring s) {
    unsigned int length;
    for(unsigned int i = 0; s[i] != '\0'; i++){
        length = i+1;
    }
    return length;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool res = false;
    unsigned int length1 = fstring_length(s1);
    unsigned int length2 = fstring_length(s2);
    if(length1 == length2){
        res = true;
        for(unsigned int i = 0;i < length1 && res; i++){
            res = res && s1[i] == s2[i];
        }
    } 
    return res;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool res = true;
    bool todos_iguales = true;
    unsigned int length1 = fstring_length(s1);
    unsigned int length2 = fstring_length(s2);
    unsigned int length = length1 <= length2 ? length1 : length2;
    for(unsigned int i = 0; i < length; i++){
        if(s1[i] != s2[i]){
            todos_iguales = false;
            res = s1[i] < s2[i];
            break;
        }
    }
    if(todos_iguales && res){
        res = length1 <= length2 ? true : false;
    }
    return res;
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1,  fixstring s2) {
    fixstring aux;
    fstring_set(aux, s2);
    fstring_set(s2, s1);
    fstring_set(s1, aux);
}


