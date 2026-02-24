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

    for (int i = 0, j = n - 1; i < j; ++i, --j) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    for (int i = 0; i < n; ++i) {
        if (i) putchar(' ');
        printf("%d", a[i]);
    }
    putchar('\n');

    free(a);
    return 0;
}