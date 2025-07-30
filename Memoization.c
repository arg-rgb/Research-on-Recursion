
#include <stdio.h>
#include <string.h>

#define MAX 1000
int memo[MAX];

int fib_fast(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = fib_fast(n - 1) + fib_fast(n - 2);
    return memo[n];
}

int main(void) {
    memset(memo, -1, sizeof(memo));
    int n = 20;
    printf("Memoized Fibonacci(%d): %d\n", n, fib_fast(n));
    return 0;
}
