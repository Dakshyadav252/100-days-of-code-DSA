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

static int dfs_topo(int u, List *adj, int *state, int *order, int *ord_sz) {
    state[u] = 1; /* visiting */
    for (int i = 0; i < adj[u].sz; ++i) {
        int v = adj[u].data[i];
        if (v < 0) continue;
        if (state[v] == 0) {
            if (!dfs_topo(v, adj, state, order, ord_sz)) return 0;
        } else if (state[v] == 1) {
            /* back edge -> cycle */
            return 0;
        }
    }
    state[u] = 2; /* done */
    order[(*ord_sz)++] = u;
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
        if (u >= 1 && u <= n) ui = u - 1; else if (u >= 0 && u < n) ui = u;
        if (v >= 1 && v <= n) vi = v - 1; else if (v >= 0 && v < n) vi = v;
        if (ui < 0 || vi < 0) continue;
        list_add(&adj[ui], vi); /* directed edge ui -> vi */
    }

    int *state = calloc(n, sizeof(int)); /* 0 unvisited,1 visiting,2 done */
    int *order = malloc(sizeof(int) * n);
    if (!state || !order) {
        free(state); free(order);
        for (int i = 0; i < n; ++i) free(adj[i].data);
        free(adj);
        return 0;
    }

    int ord_sz = 0;
    for (int i = 0; i < n; ++i) {
        if (state[i] == 0) {
            if (!dfs_topo(i, adj, state, order, &ord_sz)) {
                printf("IMPOSSIBLE\n");
                free(state); free(order);
                for (int j = 0; j < n; ++j) free(adj[j].data);
                free(adj);
                return 0;
            }
        }
    }

    /* order array has nodes in reverse topological order */
    for (int i = ord_sz - 1, first = 1; i >= 0; --i) {
        if (!first) printf(" ");
        first = 0;
        printf("%d", order[i]);
    }
    printf("\n");

    free(state);
    free(order);
    for (int i = 0; i < n; ++i) free(adj[i].data);