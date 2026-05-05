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
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    List *adj = calloc((size_t)n, sizeof(List));
    if (!adj) return 0;

    /* input: for each vertex i: k v1 v2 ... vk (neighbors may be 0-based or 1-based) */
    for (int i = 0; i < n; ++i) {
        int k;
        if (scanf("%d", &k) != 1) { k = 0; }
        for (int j = 0; j < k; ++j) {
            int v;
            if (scanf("%d", &v) != 1) break;
            int vi = -1;
            if (v >= 1 && v <= n) vi = v - 1;
            else if (v >= 0 && v < n) vi = v;
            if (vi >= 0) list_add(&adj[i], vi);
        }
    }

    int s;
    if (scanf("%d", &s) != 1) {
        for (int i = 0; i < n; ++i) free(adj[i].data);
        free(adj);
        return 0;
    }
    int si = (s >= 1 && s <= n) ? s - 1 : s;
    if (si < 0 || si >= n) {
        for (int i = 0; i < n; ++i) free(adj[i].data);
        free(adj);
        return 0;
    }

    int *vis = calloc(n, sizeof(int));
    if (!vis) { for (int i = 0; i < n; ++i) free(adj[i].data); free(adj); return 0; }

    int *q = malloc(sizeof(int) * n);
    if (!q) { free(vis); for (int i = 0; i < n; ++i) free(adj[i].data); free(adj); return 0; }
    int head = 0, tail = 0;

    vis[si] = 1;
    q[tail++] = si;

    int first = 1;
    while (head < tail) {
        int u = q[head++];
        if (!first) printf(" ");
        first = 0;
        printf("%d", u);
        for (int i = 0; i < adj[u].sz; ++i) {
            int v = adj[u].data[i];
            if (v < 0 || v >= n) continue;
            if (!vis[v]) {
                vis[v] = 1;
                q[tail++] = v;
            }
        }
    }
    printf("\n");

    free(q);
    free(vis);
    for (int i = 0; i < n; ++i) free(adj[i].data);
    free(adj);
    return 0;
}