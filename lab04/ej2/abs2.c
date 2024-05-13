#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void absolute(int x, int *y) {
    *y = x > 0 ? x : -x;
}

int main(void) {
    int a=0, res=0;
    a = -10;
    int *p = NULL;
    p = &res;
    absolute(a, p);
    printf("%d \n", res);

    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}

// int *y es de tipo in, y C tiene solo parametros de tipo in.