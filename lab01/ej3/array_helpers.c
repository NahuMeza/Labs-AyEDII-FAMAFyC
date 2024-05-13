
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int array_from_file(int array[], const char *filepath) {

    FILE* FILE = fopen(filepath, "r");
    int length;
    fscanf(FILE, "%d", &length);

    for(int i = 0; i < length; i++){
        fscanf(FILE, "%d", &array[i]);
    }

    fclose(FILE);

    return length;
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    for(unsigned int i = 0; i < length - 1; i++) {
        printf(" %d,", a[i]);
    }
    printf(" %d ] \n", a[length-1]);
}
