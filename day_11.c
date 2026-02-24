#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) return 0;
    int total = m * n;
    int *a = malloc(sizeof(int) * total);
    int *b = malloc(sizeof(int) * total);
    if (!a || !b) {
        free(a); free(b);
        return 0;
    }
    for (int i = 0; i < total; ++i) {
        if (scanf("%d", &a[i]) != 1) { free(a); free(b); return 0; }
    }
    for (int i = 0; i < total; ++i) {
        if (scanf("%d", &b[i]) != 1) { free(a); free(b); return 0; }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int idx = i * n + j;
            printf("%d", a[idx] + b[idx]);
            if (j + 1 < n) putchar(' ');
        }
        putchar('\n');
    }
    free(a);
    free(b);
    return 0;
}