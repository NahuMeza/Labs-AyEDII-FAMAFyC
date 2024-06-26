#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pair.h"

struct s_pair_t {
    int fst;
    int snd;
};

pair_t pair_new(int x, int y){
    pair_t pair = malloc(sizeof(pair_t));
    pair -> fst = x;
    pair -> snd = y;
    return pair;
}

int pair_first(pair_t p){
    return p->fst;
}

int pair_second(pair_t p){
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    return pair_new(pair_second(p), pair_first(p));
}

pair_t pair_destroy(pair_t p){
    free(p);
    return NULL;
}
