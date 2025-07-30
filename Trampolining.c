#include <stdio.h>
#include <stdlib.h>

typedef struct Thunk {
    struct Thunk* (*fn)(void*);
    void* ctx;
} Thunk;

Thunk* count_down(void* c) {
    int* n = (int*)c;
    if (*n == 0) {
        printf("Countdown done.\n");
        free(n);
        return NULL;
    }
    printf("%d\n", *n);
    int* next = malloc(sizeof(int));
    *next = *n - 1;
    return &(Thunk){count_down, next};
}

void trampoline(Thunk* t) {
    while (t) {
        Thunk* next = t->fn(t->ctx);
        // Do not free t pointer, as it was on stack for the initial call
        t = next;
    }
}

int main(void) {
    int* start = malloc(sizeof(int));
    *start = 5;
    Thunk t = {count_down, start};
    trampoline(&t);
    return 0;
}
