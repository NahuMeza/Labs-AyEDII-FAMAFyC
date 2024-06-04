#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>

#include "stringbuffer.h"

struct s_stringbuffer {
    struct s_node *first;
    struct s_node *last;
    unsigned int length;
};

struct s_node {
    char c;
    struct s_node *nextchar;
};

typedef struct s_node * node_t;

// Representation invariant
static bool invrep(stringbuffer sb) {
    bool valid=false;
    valid = sb != NULL;

    if(valid && sb->first != NULL){
        valid = valid && (sb->last != NULL);
    }
    if(valid && sb->last != NULL){
        valid = valid && (sb->last->nextchar == NULL);
    }

    return valid;
}


// Creates a single node in dynamic memory with a given char
static node_t create_node(char c) {
    node_t newnode=NULL;    
    newnode = malloc(sizeof(struct s_node));
    newnode->c = c;
    newnode->nextchar = NULL;
    assert(newnode!=NULL);
    return newnode;
}


// Destroy a single node
static node_t destroy_node(node_t node) {
    free(node);
    node = NULL;
    assert(node==NULL);
    return node;
}


// Public functions of the Abstract Data Type
stringbuffer stringbuffer_empty(void) {
    stringbuffer sb = NULL;
    sb = malloc(sizeof(struct s_stringbuffer));
    sb->first = NULL;
    sb->last = NULL;
    sb->length = 0;
    assert(invrep(sb) && stringbuffer_is_empty(sb));
    return sb;
}


stringbuffer stringbuffer_create(const char *word) {
    assert(word!=NULL);
    node_t newnode = NULL;
    node_t first = NULL;
    node_t last = NULL;

    unsigned int w_length = strlen(word);
    first = create_node(word[0]);
    last = create_node(word[w_length - 1]);

    stringbuffer sb = stringbuffer_empty();
    sb->first = first;

    node_t p = sb->first;
    for(unsigned int i = 1; i < w_length - 1; i++){
        newnode = create_node(word[i]);
        p->nextchar = newnode;
        p = p->nextchar;
    }

    p->nextchar = last;
    sb->last = p->nextchar;
    sb->length = w_length;

    assert(invrep(sb));
    return sb;
}


bool stringbuffer_is_empty(stringbuffer sb){
    assert(invrep(sb));
    return sb->length == 0;
}


stringbuffer stringbuffer_append(stringbuffer sb, const char c) {
    assert(invrep(sb));
    node_t new_node = create_node(c);
    if(sb->length == 0){
        sb->first = new_node;
        sb->last = sb->first;
    }
    else{
        sb->last->nextchar = new_node;
        sb->last = sb->last->nextchar;
    }
    sb->length++;

    assert(invrep(sb) && !stringbuffer_is_empty(sb));
    return sb;
}


char stringbuffer_char_at(stringbuffer sb, unsigned int index) {
    assert(invrep(sb) && !stringbuffer_is_empty(sb) && index<stringbuffer_length(sb));
    unsigned pos = 0;
    node_t node = sb->first;
    while(pos < index) {
        node = node->nextchar;
        pos++;
    }

    assert(invrep(sb));
    return node->c;
}


stringbuffer stringbuffer_remove(stringbuffer sb, unsigned int index) {
    assert(invrep(sb));
    node_t node=sb->first, prev=NULL;

    if(index < stringbuffer_length(sb)){
        if(index == 0){
            prev = node;
            sb->first = prev->nextchar;
            node = destroy_node(node);
        }
        else{
            for(unsigned int i = 0; i < index; i++){
                prev = node;
                node = node->nextchar;
            }
            if(sb->last == node){
                sb->last = prev;
            }
            prev->nextchar = node->nextchar;
            node = destroy_node(node);
            sb->length--;
        }
    }
    assert(invrep(sb));
    return sb;
}


stringbuffer stringbuffer_replace(stringbuffer sb, const char c, unsigned int index) {
    assert(invrep(sb) && index < stringbuffer_length(sb));
    
    if(index == (stringbuffer_length(sb) - 1)){
        sb->last->c = c;
    }
    else{
        node_t p = NULL;
        p = sb->first;
        for(unsigned int i = 0; i < index; i++){
            p = p->nextchar;
        }
        p->c = c;
    }

    assert(invrep(sb));
    return sb;
}


unsigned int stringbuffer_length(stringbuffer sb) {
    assert(invrep(sb));
    unsigned int length = sb->length;
    assert(invrep(sb) && stringbuffer_is_empty(sb) == (length == 0));
    return length;
}


char* stringbuffer_to_string(stringbuffer sb) {
    assert(invrep(sb));
    char* str = NULL;
    unsigned int sb_len = sb->length;
    if(!stringbuffer_is_empty(sb)){
        str = malloc(sizeof(char)*(sb_len+1));
        node_t p = sb->first;
        for(unsigned int i = 0; i < sb_len; i++){
            str[i] = p->c;
            p = p->nextchar;
        }
        str[sb_len] = '\0';
    }

    assert(invrep(sb) && stringbuffer_is_empty(sb) == (str == NULL));
    return str;
}


void stringbuffer_dump(stringbuffer sb) {
    assert(invrep(sb));
    node_t node = sb->first;
    while (node != NULL) {
        printf("%c", node->c);
        node = node->nextchar;
    }
    printf("\n");
}


stringbuffer stringbuffer_destroy(stringbuffer sb) {
    assert(invrep(sb));
    node_t p = NULL, q = NULL;
    p = sb->first;

    while(p != NULL){
        q = p->nextchar;
        p = destroy_node(p);
        p = q;
    }

    free(sb);
    sb = NULL;
    assert(sb == NULL);
    return sb;
}
