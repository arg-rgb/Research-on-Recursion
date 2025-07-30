#include <stdio.h>
#include <setjmp.h>

typedef struct {
    int val;
    int n;
    jmp_buf buf;
    int state;
} Coroutine;

int gen(Coroutine* coro) {
    switch (coro->state) {
        case 0: // start
            coro->val = 0;
            for (int i = 0; i < coro->n; ++i) {
                coro->val = i;
                coro->state = 1;
                if (!setjmp(coro->buf)) return 1;
                // resume here after longjmp
            }
    }
    coro->state = 2;
    return 0; // end
}

int main(void) {
    Coroutine coro = {.n = 5, .state = 0};
    while (gen(&coro)) {
        printf("Yielded %d\n", coro.val);
        longjmp(coro.buf, 1); // resume coroutine after yield
    }
    printf("Coroutine finished.\n");
    return 0;
}
