#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter c = NULL;
    c = malloc(sizeof(struct _counter));
    c->count = 0;
    return c;
}

void counter_inc(counter c) {
    c->count++;
}

bool counter_is_init(counter c) {
    return c->count == 0 && c != NULL;
}

void counter_dec(counter c) {
    assert(!counter_is_init(c));
    c->count--;
}

counter counter_copy(counter c) {
    counter cc = NULL;
    cc = malloc(sizeof(struct _counter));
    cc->count = c->count;
    return cc;
}

void counter_destroy(counter c) {
    free(c);
    c = NULL;
}
