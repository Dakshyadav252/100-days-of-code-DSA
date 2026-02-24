#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int p;
    if (scanf("%d", &p) != 1) return 0;
    if (p < 0) return 0;

    int *a = NULL;
    if (p > 0) {
        a = malloc(p * sizeof *a);
        if (!a) return 0;
        for (int i = 0; i < p; ++i) {
            if (scanf("%d", &a[i]) != 1) { free(a); return 0; }
        }
    }

    int q;
    if (scanf("%d", &q) != 1) { free(a); return 0; }
    if (q < 0) { free(a); return 0; }

    int *b = NULL;
    if (q > 0) {
        b = malloc(q * sizeof *b);
        if (!b) { free(a); return 0; }
        for (int i = 0; i < q; ++i) {
            if (scanf("%d", &b[i]) != 1) { free(a); free(b); return 0; }
        }
    }

    int i = 0, j = 0;
    int first = 1;
    while (i < p && j < q) {
        int val = (a[i] <= b[j]) ? a[i++] : b[j++];
        if (!first) putchar(' ');
        first = 0;
        printf("%d", val);
    }
    while (i < p) {
        if (!first) putchar(' ');
        first = 0;
        printf("%d", a[i++]);
    }
    while (j < q) {
        if (!first) putchar(' ');
        first = 0;
        printf("%d", b[j++]);
    }
    putchar('\n');

    free(a);
    free(b);
    return 0;
}