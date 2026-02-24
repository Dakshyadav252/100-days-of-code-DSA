#include <stdio.h>

long long fib(int n) {
    if (n < 2) return n; // fib(0)=0, fib(1)=1
    return fib(n - 1) + fib(n - 2);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    printf("%lld\n", fib(n));
    return 0;
}