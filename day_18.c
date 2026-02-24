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

    int k;
    if (scanf("%d", &k) != 1) { free(a); return 0; }
    k = ((k % n) + n) % n; // handle k >= n and negative k

    if (k == 0) {
        for (int i = 0; i < n; ++i) {
            if (i) printf(" ");
            printf("%d", a[i]);
        }
        printf("\n");
        free(a);
        return 0;
    }

    int *b = malloc(n * sizeof *b);
    if (!b) { free(a); return 0; }

    for (int i = 0; i < n; ++i) {
        b[(i + k) % n] = a[i];
    }

    for (int i = 0; i < n; ++i) {
        if (i) printf(" ");
        printf("%d", b[i]);
    }
    printf("\n");

    free(a);
    free(b);
    return 0;
}