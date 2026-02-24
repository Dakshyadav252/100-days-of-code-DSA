#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n <= 0) { putchar('\n'); return 0; }

    int *a = malloc(n * sizeof *a);
    if (!a) return 0;

    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &a[i]) != 1) { free(a); return 0; }
    }

    int write = 0;
    for (int i = 0; i < n; ++i) {
        if (write == 0 || a[i] != a[write - 1]) {
            a[write++] = a[i];
        }
    }

    for (int i = 0; i < write; ++i) {
        if (i) putchar(' ');
        printf("%d", a[i]);
    }
    putchar('\n');

    free(a);
    return 0;
}