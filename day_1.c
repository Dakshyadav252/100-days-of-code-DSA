#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *a = malloc((n + 1) * sizeof *a);
    if (!a) return 0;

    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &a[i]) != 1) { free(a); return 0; }
    }

    int pos, x;
    if (scanf("%d", &pos) != 1) { free(a); return 0; }
    if (scanf("%d", &x) != 1) { free(a); return 0; }

    if (pos < 1) pos = 1;
    if (pos > n + 1) pos = n + 1;

    for (int i = n; i >= pos; --i) {
        a[i] = a[i - 1];
    }
    a[pos - 1] = x;

    for (int i = 0; i <= n; ++i) {
        if (i) putchar(' ');
        printf("%d", a[i]);
    }
    putchar('\n');

    free(a);
    return 0;
}