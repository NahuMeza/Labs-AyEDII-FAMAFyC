#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

struct e_node_ {
    list_elem elem;
    struct e_node_ *next;
};

list empty_list(void){
    list l = NULL;
    return l;
}

list addl_list(list l, list_elem e){
    list p = NULL;
    p = malloc(sizeof(struct e_node_));
    p->elem = e;
    p->next = l;
    l = p;
    p = NULL;
    return l;
}

list destroy_list(list l){
    if(l != NULL){
        destroy_list(l->next);
        free(l);
    };
    return l;
}

bool is_empty_list(list l){
    return l == NULL;
}

list_elem head(list l){
    assert(!is_empty_list(l));
    return l->elem;
}

list tail(list l){
    assert(!is_empty_list(l));
    list p = l;
    l = l->next;
    free(p);
    return l;
}

list addr_list(list l, list_elem e){
    list p,q = l;
    p = malloc(sizeof(struct e_node_));
    p -> elem = e;
    p -> next = NULL;
    if(!is_empty_list(l)){
        while(q->next != NULL){
            q = q -> next;
        }
        q->next = p;
        q = NULL;
        p = NULL;
    }
    else{
        l = p;
    }
    return l;
}

unsigned int length_list(list l){
    unsigned int length = 0;
    list q = l;
    while(q != NULL){
        q = q -> next;
        length++;
    }
    return length;
}

list concat_list(list l, list lx){
    list q = l;
    while(q->next != NULL){
        q = q -> next;
    }
    q->next = lx;
    return l;
}

list_elem index_list(list l, unsigned int n){
    assert(length_list(l) > n);
    list p = l;
    while(n > 0){
        p = p->next;
        n--;
    }
    return p->elem;
}

list take_list(list l, unsigned int n){
    assert(length_list(l) > n);
    list p = l;
    while(n > 0){
        p = p->next;
        n--;
    }
    destroy_list(p);
    return l;
}

list drop_list(list l, unsigned int n){
    assert(length_list(l) > n);
    list p = l;
    while(n > 0){
        l = l -> next;
        tail(p);
        p = l;
        n--;
    }
    return l;
}

list copy_list(list l){
    list l2;
    if(l != NULL){
        l2 = empty_list();
        l2 = addr_list(l2, l->elem);
        l2->next = copy_list(l->next);
    }
    return l2;
}