/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

unsigned int array_from_stdin(int array[]) {
    
    FILE* FILE = stdin;
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


int main() {
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_stdin(array);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
