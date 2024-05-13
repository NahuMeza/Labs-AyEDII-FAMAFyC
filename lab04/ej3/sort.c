/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    return x->rank <= y->rank;
    return true;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}


void swap(player_t a[], int i, int j){
    player_t tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv = izq;
    unsigned int i = izq++;
    unsigned int j = der;
    while(j>=i){
        if(goes_before(a[i], a[ppiv])){
            i++;
        }
        else if(goes_before(a[ppiv], a[j])){
            j--;
        }
        else {
            swap(a,i,j);
            i++;
            j--;
        }
    }
    swap(a,j,ppiv);
    ppiv = j;
    return ppiv;
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv;
    if (der>izq){
        ppiv = partition(a,izq,der);
        quick_sort_rec(a,izq,ppiv == 0 ? 0 : ppiv-1);
        quick_sort_rec(a,ppiv+1,der);
    }
}

void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}
