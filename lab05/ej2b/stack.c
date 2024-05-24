#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack {
    stack_elem elem;
    struct _s_stack *next;
    unsigned int size;  // add this tuple
};

stack stack_empty() {
    stack s = NULL; 
    return s;
}

stack stack_push(stack s, stack_elem e) {
    // add top to the beginning of the stack
    stack p = NULL;
    p = malloc(sizeof(struct _s_stack));

    p->elem = e;
    p->size = (s == NULL) ? 1 : s->size + 1;
    p->next = s;

    return p;
}

stack stack_pop(stack s) {
    assert(stack_size(s) != 0);
    stack p = NULL;
    p = s->next;
    s->next = NULL;
    free(s);
    return p;
}

unsigned int stack_size(stack s) {
    return (s == NULL) ? 0 : s->size;
}

stack_elem stack_top(stack s) {
    assert(stack_size != 0);
    return s->elem;
}

bool stack_is_empty(stack s) {
    return (s == NULL);
}

stack_elem *stack_to_array(stack s) {
    assert(s != NULL);
    stack_elem *arr = NULL;
    unsigned int size = s->size;

    if(s != NULL) {
        arr = malloc(s->size*sizeof(struct _s_stack));
        stack p = NULL;
        p = s;
        for(unsigned int i = 0; i < size; i++){
            arr[i] = p->elem;
            p = p->next;
        }
    }
    return arr;
}

stack stack_destroy(stack s) {
    stack p = NULL;
    while(s != NULL) {
        p = s;
        s = s->next;
        p->next = NULL;
        free(p);
    }
    return s;
}