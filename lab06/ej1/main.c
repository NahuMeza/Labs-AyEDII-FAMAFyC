/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    bool finish = false;
    int option;
    while(!finish){
        printf("Elija una de las siguientes opciones: \n\n");
        printf("1 ........ Mostrar árbol por pantalla \n"
        "2 ........ Agregar un elemento \n"
        "3 ........ Eliminar un elemento \n"
        "4 ........ Chequear existencia de elemento \n"
        "5 ........ Mostrar longitud del árbol\n"
        "6 ........ Mostrar raiz, máximo y mínimo del árbol\n"
        "7 ........ Salir\n");
        scanf("%d", &option);
        if(option == 7){
            finish = true;
        }
        else if(option == 1){
            abb_dump(tree, ABB_PRE_ORDER);
            printf("\n");
        }
        else if(option == 2){
            printf("Indique el elemento deseado: \n");
            scanf("%d", &option);
            tree = abb_add(tree, option);
        }
        else if(option == 3){
            printf("Indique el elemento a eliminar: \n");
            scanf("%d", &option);
            tree = abb_remove(tree, option);
        }
        else if(option == 4){
            bool e;
            printf("Indique el elemento a chequear: \n");
            scanf("%d", &option);
            e = abb_exists(tree, option);
            printf("El elemento deseado %s existe \n\n", e ? "SI" : "NO");
        }
        else if(option == 5){
            printf("El arbol es de longitud: %d \n\n", abb_length(tree));
        }
        else if(option == 6){
            if (!abb_is_empty(tree)) {
            printf("\n");
            printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),
                                                        abb_min(tree),
                                                        abb_max(tree));
            } else {
                printf("\nÁrbol vacío\n");
            }
        }
        else{
            printf("no existe la opcion correspondiente \n\n");
        }
    }
    tree = abb_destroy(tree);
    return (EXIT_SUCCESS);
}
