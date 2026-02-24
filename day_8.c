#include <stdio.h>

long long pow_rec(long long a, long long b) {
    if (b == 0) return 1;
    if (b % 2 == 0) {
        long long half = pow_rec(a, b / 2);
        return half * half;
    } else {
        return a * pow_rec(a, b - 1);
    }
}

int main(void) {
    long long a, b;
    if (scanf("%lld %lld", &a, &b) != 2) return 0;
    if (b < 0) {
        double res = 1.0 / (double)pow_rec(a, -b); // prints fractional for negative exponent
        printf("%g\n", res);
    } else {
        printf("%lld\n", pow_rec(a, b));
    }
    return 0;
}