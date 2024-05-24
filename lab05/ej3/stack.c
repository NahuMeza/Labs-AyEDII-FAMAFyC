#include <stdlib.h>
#include <assert.h>
#include "stack.h"

#define MAX_CAPACITY 100

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

stack stack_empty() {
    stack s = NULL; 
    return s;
}

stack stack_push(stack s, stack_elem e) {
    stack nstack = NULL;
    if(s == NULL){
        nstack = malloc(sizeof(struct _s_stack));

        nstack->capacity = MAX_CAPACITY;
        nstack->size = 1;

        nstack->elems = malloc(nstack->capacity*sizeof(stack_elem));
        nstack->elems[0] = e;
    }
    else{
        nstack = s;
        unsigned int size = nstack->size;
        unsigned int capacity = nstack->capacity;

        if(size == capacity){
            nstack->capacity = capacity * 2;
            nstack->elems = realloc(nstack->elems, capacity*sizeof(stack_elem));
        }

        nstack->elems[size] = e;
        nstack->size = size + 1;
        
    }
    return nstack;
}

stack stack_pop(stack s) {
    assert(stack_size(s) != 0);
    if(stack_size(s) == 1){
        free(s);
        s = NULL;
    }
    else{
        s->size = s->size - 1;
    }
    return s;
}

unsigned int stack_size(stack s) {
    return (s == NULL) ? 0 : s->size;
}

stack_elem stack_top(stack s) {
    assert(stack_size != 0);
    return s->elems[s->size-1];
}

bool stack_is_empty(stack s) {
    return (s == NULL);
}

stack_elem *stack_to_array(stack s) {
    stack_elem *arr = NULL;
    unsigned int size = s->size;

    if(s != NULL) {
        arr = malloc(s->size*sizeof(struct _s_stack));
        for(unsigned int i = 0; i < size; i++){
            arr[i] = s->elems[i];
        }
    }

    return arr;
}

stack stack_destroy(stack s) {
    free(s);
    s = NULL;
    return s;
}