#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    if (n <= 0) return 0;

    int *mat = calloc((size_t)n * n, sizeof(int));
    if (!mat) return 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) break;
        int ui = -1, vi = -1;
        /* accept 1-based or 0-based indices */
        if (u >= 1 && u <= n) ui = u - 1;
        else if (u >= 0 && u < n) ui = u;
        if (v >= 1 && v <= n) vi = v - 1;
        else if (v >= 0 && v < n) vi = v;
        if (ui < 0 || vi < 0) continue;
        /* treat as undirected: mark both entries */
        mat[ui * n + vi] = 1;
        mat[vi * n + ui] = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) printf(" ");
            printf("%d", mat[i * n + j]);
        }
        printf("\n");
    }

    free(mat);
    return 0;
}