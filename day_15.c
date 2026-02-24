#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) return 0;
    if (m <= 0 || n <= 0) return 0;

    long long sum = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int val;
            if (scanf("%d", &val) != 1) return 0;
            if (i == j) sum += val;
        }
    }

    printf("%lld\n", sum);
    return 0;