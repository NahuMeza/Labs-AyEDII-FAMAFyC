#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem elem;
    stack next;
};

stack stack_empty(){
    stack st = NULL;
    return st;
}

stack stack_destroy(stack s){
    if(s != NULL){
        stack_destroy(s->next);
        free(s);
    }
    return s;
}

stack stack_push(stack s, stack_elem e){
    stack st = malloc(sizeof(struct _s_stack)), p;
    st->elem = e;
    st->next = NULL;
    if(s != NULL){
        p = s;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = st;
    }
    else{
        s = st;
    }
    return s;
}

stack stack_pop(stack s){
    assert(s != NULL);

    if (s->next == NULL) {
        // Caso especial: la pila tiene solo un elemento
        stack_destroy(s);
        return NULL;
    }

    stack p = s;
    // Encontrar el penúltimo nodo
    while (p->next->next != NULL) {
        p = p->next;
    }

    // p ahora apunta al penúltimo nodo
    stack_destroy(p->next);  // Destruir el último nodo
    p->next = NULL;  // Desconectar el último nodo

    return s;
}

unsigned int stack_size(stack s){
    unsigned int res = 0;
    stack p = NULL;
    p = s;
    while(p != NULL){
        res++;
        p = p->next;
    }
    return res;
}

stack_elem stack_top(stack s){
    assert(s != NULL);
    stack p;
    p = s;
    while(p->next != NULL){
        p = p->next;
    }
    return p->elem;
}

bool stack_is_empty(stack s){
    return s == NULL;
}

stack_elem *stack_to_array(stack s){
    unsigned int ssize = stack_size(s);
    stack_elem *res = NULL;
    if(s != NULL){
        res = malloc(sizeof(stack_elem) * ssize);
        stack p = NULL;
        p = s;
        for(unsigned int i = 0; i < ssize; i++){
            res[i] = p->elem;
            p = p->next;
        }
    }
    return res;
}