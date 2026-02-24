#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n <= 0) return 0;

    int val;
    if (scanf("%d", &val) != 1) return 0;
    int max = val, min = val;

    for (int i = 1; i < n; ++i) {
        if (scanf("%d", &val) != 1) return 0;
        if (val > max) max = val;
        if (val < min) min = val;
    }

    printf("Max: %d\n", max);
    printf("Min: %d\n", min);

    return 0;
}