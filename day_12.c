#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) return 0;

    int **a = malloc(m * sizeof *a);
    if (!a) return 0;
    for (int i = 0; i < m; ++i) {
        a[i] = malloc(n * sizeof **a);
        if (!a[i]) return 0;
    }

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &a[i][j]);

    int symmetric = 1;
    if (m != n) symmetric = 0;
    else {
        for (int i = 0; i < m && symmetric; ++i)
            for (int j = i + 1; j < n; ++j)
                if (a[i][j] != a[j][i]) { symmetric = 0; break; }
    }

    if (symmetric) printf("Symmetric Matrix");
    else printf("Not a Symmetric Matrix");

    for (int i = 0; i < m; ++i) free(a[i]);
    free(a);
    return 0;
}