#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int parse_file( int argc, char const *argv[], char letters[], unsigned int indexes[]){
    if (argc != 2) exit(EXIT_FAILURE);
    FILE *file = fopen(argv[1], "r");
    unsigned int i = 0;
    char tmp;
    if(feof(file)) exit(EXIT_FAILURE);
    fscanf(file,"%u", &indexes[i]);

    while(!feof(file)){
        fscanf(file,"%c", &tmp);
        if(tmp == '*'){
            fscanf(file,"%c", &letters[i]);
            fscanf(file,"%c", &tmp);
            if (tmp != '*') exit(EXIT_FAILURE);
            i++;
            if(!feof(file)){
                fscanf(file,"%u", &indexes[i]);
            }
        }
        if(i >= MAX_SIZE) exit(EXIT_FAILURE);
    }

    fclose(file);
    printf("%u \n", i);
    return i;
}

int main(int argc, char const *argv[]) {
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 
    printf("antes de entrar a la funcion \n");
    length = parse_file( argc, argv, letters, indexes);

    for(unsigned int i = 0; i < length; i++){
        if(indexes[i] >= MAX_SIZE){
            printf("el indice supera el tamaño maximo");
            exit(EXIT_FAILURE);
        }
        sorted[indexes[i]] = letters[i];
    }

    dump(sorted, length);

    return EXIT_SUCCESS;
}


