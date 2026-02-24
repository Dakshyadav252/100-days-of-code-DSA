#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n <= 0) return 0;

    int *a = malloc(n * sizeof *a);
    if (!a) return 0;

    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &a[i]) != 1) { free(a); return 0; }
    }

    int pos;
    if (scanf("%d", &pos) != 1) { free(a); return 0; }

    if (pos < 1) pos = 1;
    if (pos > n) pos = n;

    for (int i = pos - 1; i < n - 1; ++i) {
        a[i] = a[i + 1];
    }

    for (int i = 0; i < n - 1; ++i) {
        if (i) putchar(' ');
        printf("%d", a[i]);
    }
    putchar('\n');

    free(a);
    return 0;
}