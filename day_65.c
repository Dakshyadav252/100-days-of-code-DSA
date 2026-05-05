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

static int dfs_cycle(int u, int parent, List *adj, int *vis, int n) {
    vis[u] = 1;
    for (int i = 0; i < adj[u].sz; ++i) {
        int v = adj[u].data[i];
        if (v < 0 || v >= n) continue;
        if (!vis[v]) {
            if (dfs_cycle(v, u, adj, vis, n)) return 1;
        } else if (v != parent) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    if (n <= 0) { printf("NO\n"); return 0; }

    List *adj = calloc((size_t)n, sizeof(List));
    if (!adj) return 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) break;
        int ui = -1, vi = -1;
        if (u >= 1 && u <= n) ui = u - 1; else if (u >= 0 && u < n) ui = u;
        if (v >= 1 && v <= n) vi = v - 1; else if (v >= 0 && v < n) vi = v;
        if (ui < 0 || vi < 0) continue;
        list_add(&adj[ui], vi);
        list_add(&adj[vi], ui);
    }

    int *vis = calloc(n, sizeof(int));
    if (!vis) { for (int i = 0; i < n; ++i) free(adj[i].data); free(adj); return 0; }

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            if (dfs_cycle(i, -1, adj, vis, n)) {
                printf("YES\n");
                free(vis);
                for (int j = 0; j < n; ++j) free(adj[j].data);
                free(adj);
                return 0;
            }
        }
    }

    printf("NO\n");
    free(vis);
    for (int i = 0; i < n; ++i) free(adj[i].data);
    free(adj);
    return 0;
}
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

static int dfs_cycle(int u, int parent, List *adj, int *vis, int n) {
    vis[u] = 1;
    for (int i = 0; i < adj[u].sz; ++i) {
        int v = adj[u].data[i];
        if (v < 0 || v >= n) continue;
        if (!vis[v]) {
            if (dfs_cycle(v, u, adj, vis, n)) return 1;
        } else if (v != parent) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    if (n <= 0) { printf("NO\n"); return 0; }

    List *adj = calloc((size_t)n, sizeof(List));
    if (!adj) return 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) break;
        int ui = -1, vi = -1;
        if (u >= 1 && u <= n) ui = u - 1; else if (u >= 0 && u < n) ui = u;
        if (v >= 1 && v <= n) vi = v - 1; else if (v >= 0 && v < n) vi = v;
        if (ui < 0 || vi < 0) continue;
        list_add(&adj[ui], vi);
        list_add(&adj[vi], ui);
    }

    int *vis = calloc(n, sizeof(int));
    if (!vis) { for (int i = 0; i < n; ++i) free(adj[i].data); free(adj); return 0; }

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            if (dfs_cycle(i, -1, adj, vis, n)) {
                printf("YES\n");
                free(vis);
                for (int j = 0; j < n; ++j) free(adj[j].data);
                free(adj);
                return 0;
            }
        }
    }

    printf("NO\n");
    free(vis);
    for (int i = 0; i < n; ++i) free(adj[i].data);
    free(adj);
    return 0;
}
