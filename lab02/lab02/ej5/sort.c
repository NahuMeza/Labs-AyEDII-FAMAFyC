#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"


static unsigned int partition(fixstring a[], unsigned int izq, unsigned int der) {
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

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv;
    if (der>izq){
        ppiv = partition(a,izq,der);
        quick_sort_rec(a,izq,ppiv == 0 ? 0 : ppiv-1);
        quick_sort_rec(a,ppiv+1,der);
    }
}

void quick_sort(fixstring a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}


