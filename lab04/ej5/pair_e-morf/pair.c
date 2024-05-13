#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pair.h"

struct s_pair_t {
    elem fst;
    elem snd;
};

pair_t pair_new(elem x, elem y){
    pair_t pair = malloc(sizeof(pair_t));
    pair -> fst = x;
    pair -> snd = y;
    return pair;
}

elem pair_first(pair_t p){
    return p->fst;
}

elem pair_second(pair_t p){
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    return pair_new(pair_second(p), pair_first(p));
}

pair_t pair_destroy(pair_t p){
    free(p);
    return NULL;
}
