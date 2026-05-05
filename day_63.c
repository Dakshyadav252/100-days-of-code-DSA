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

static void dfs_rec(int u, List *adj, int *vis, int n, int *first) {
    vis[u] = 1;
    if (!*first) printf(" ");
    *first = 0;
    printf("%d", u);
    for (int i = 0; i < adj[u].sz; ++i) {
        int v = adj[u].data[i];
        if (v < 0 || v >= n) continue;
        if (!vis[v]) dfs_rec(v, adj, vis, n, first);
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    List *adj = calloc((size_t)n, sizeof(List));
    if (!adj) return 0;

    /* Expected input for each vertex: k v1 v2 ... vk
       where k is number of neighbours. Neighbours may be 0-based or 1-based. */
    for (int i = 0; i < n; ++i) {
        int k;
        if (scanf("%d", &k) != 1) { /* treat missing as zero neighbours */ k = 0; }
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
    if (scanf("%d", &s) != 1) { /* no start provided -> print nothing */ 
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

    int first = 1;
    dfs_rec(si, adj, vis, n, &first);
    printf("\n");

    free(vis);
    for (int i = 0; i < n; ++i) free(adj[i].data);
    free(adj);
    return 0;
}