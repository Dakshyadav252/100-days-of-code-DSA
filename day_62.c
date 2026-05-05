#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int sz;
    int cap;
} List;

static int list_add(List *l, int v) {
    if (l->sz == l->cap) {
        int newcap = l->cap == 0 ? 4 : l->cap * 2;
        int *p = realloc(l->data, sizeof(int) * newcap);
        if (!p) return 0;
        l->data = p;
        l->cap = newcap;
    }
    l->data[l->sz++] = v;
    return 1;
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    if (n <= 0) return 0;

    List *adj = calloc((size_t)n, sizeof(List));
    if (!adj) return 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) break;
        int ui = -1, vi = -1;
        if (u >= 1 && u <= n) ui = u - 1;
        else if (u >= 0 && u < n) ui = u;
        if (v >= 1 && v <= n) vi = v - 1;
        else if (v >= 0 && v < n) vi = v;
        if (ui < 0 || vi < 0) continue;
        list_add(&adj[ui], vi);
        list_add(&adj[vi], ui); /* treat as undirected; remove if directed */
    }

    /* print adjacency lists (0-based indices) */
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < adj[i].sz; ++j) {
            if (j) printf(" ");
            printf("%d", adj[i].data[j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; ++i) free(adj[i].data);
    free(adj);
    return 0;
}