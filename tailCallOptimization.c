#include <stdio.h>

int fact_opt(int n, int acc)
{
    if (n <= 1) return acc;
    __attribute__((musttail))
    return fact_opt(n - 1, acc * n);
}

int main(void) {
    int n = 5;
    printf("Tail-call factorial(%d): %d\n", n, fact_opt(n, 1));
    return 0;
}
