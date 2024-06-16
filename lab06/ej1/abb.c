#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    bool invr = tree != NULL;
    if(invr){
        if(tree->left != NULL){
            invr = invr && (tree->elem <= tree->left->elem) && invrep(tree->left);
        }
        if(tree->right != NULL){
            invr = invr && (tree->elem >= tree->left->elem) && invrep(tree->right);
        }
    }
    return invr;
}

abb abb_empty(void) {
    abb tree;
    tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if(abb_is_empty(tree)){
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    }
    else{
        abb next_tree = tree->elem < e ? tree->right : tree->left;
        abb_add(next_tree, e);
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    is_empty = tree == NULL;
    assert(invrep(tree));
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    if(tree != NULL){
        assert(invrep(tree));
        exists = tree->elem == e || abb_exists(tree->elem < e ? tree->right : tree->left, e);
        assert(abb_length(tree)!=0 || !exists);
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    if(tree != NULL){
        assert(invrep(tree));
        length = abb_is_empty(tree) ? 0 : 1 + abb_length(tree->left) + abb_length(tree->right);
        assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    }
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    abb t = tree;
    abb tl = NULL, tr = NULL;
    while(t->elem != e){
        tl = t;
        t = t->elem < e ? t->left : t->right;
    }
    free(t);
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb t = tree;
    max_e = t->elem;
    while(t->left != NULL){
        t = t->left;
        max_e = t->elem;
    }
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb t = tree;
    min_e = t->elem;
    while(t->right != NULL){
        t = t->right;
        min_e = t->elem;
    }
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree, abb_ordtype ord) {
    assert(invrep(tree) && (ord==ABB_IN_ORDER  || 
                            ord==ABB_PRE_ORDER ||
                            ord==ABB_POST_ORDER));
    /*
     * c) Needs implementation: use the dump order indicated by `ord`
     *
     */

    // Implementing in-order as default
    if(tree != NULL) {
        abb_dump(tree->left, ord);
        printf("%d ", tree->elem);
        abb_dump(tree->right, ord);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if(tree->left != NULL){
        abb_destroy(tree->left);
    }
    if(tree->right != NULL){
        abb_destroy(tree->right);
    }
    free(tree);
    tree = NULL;
    assert(tree == NULL);
    return tree;
}

