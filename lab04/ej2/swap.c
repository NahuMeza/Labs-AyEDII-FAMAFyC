#include <stdlib.h>
#include <stdio.h>

void swap (int *x, int *y){
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

int main(void){
    int x, y;
    x = 6;
    y = 4;
    int *p = NULL;
    int *g = NULL;
    p = &x;
    g = &y;

    fprintf(stdout, "x = %d, y=%d \n", x, y);
    swap(p, g);
    fprintf(stdout, "x = %d, y=%d \n", x, y);
    return EXIT_SUCCESS;
}
