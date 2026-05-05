#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int cap;
} IntVec;

void vec_init(IntVec *v) {
    v->cap = 4;
    v->size = 0;
    v->data = malloc(sizeof(int) * v->cap);
}

void vec_push(IntVec *v, int x) {
    if (v->size == v->cap) {
        v->cap *= 2;
        v->data = realloc(v->data, sizeof(int) * v->cap);
    }
    v->data[v->size++] = x;
}

void vec_free(IntVec *v) {
    free(v->data);
}

// Usage:
// First line: n m    (n = number of vertices, m = number of directed edges)
// Next m lines: u v  (edge from u to v). Vertices are 0-based or 1-based depending on input; below we assume 0-based.
// If your input uses 1-based vertices, subtract 1 when reading edges.
int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Expected: n m\n");
        return 1;
    }

    IntVec *adj = malloc(sizeof(IntVec) * n);
    for (int i = 0; i < n; ++i) vec_init(&adj[i]);

    int *indeg = calloc(n, sizeof(int));

    for (int i = 0; i < m; ++i) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2) {
            fprintf(stderr, "Expected m edges\n");
            return 1;
        }
        // If input is 1-based, uncomment the next two lines:
        // --u;
        // --v;
        if (u < 0 || u >= n || v < 0 || v >= n) {
            fprintf(stderr, "Edge (%d,%d) out of bounds for n=%d\n", u, v, n);
            return 1;
        }
        vec_push(&adj[u], v);
        indeg[v]++;
    }

    // queue (simple array used as queue)
    int *q = malloc(sizeof(int) * n);
    int qh = 0, qt = 0;

    for (int i = 0; i < n; ++i) if (indeg[i] == 0) q[qt++] = i;

    int *order = malloc(sizeof(int) * n);
    int cnt = 0;

    while (qh < qt) {
        int u = q[qh++];
        order[cnt++] = u;
        for (int k = 0; k < adj[u].size; ++k) {
            int v = adj[u].data[k];
            indeg[v]--;
            if (indeg[v] == 0) q[qt++] = v;
        }
    }

    if (cnt != n) {
        printf("Graph has a cycle; topological sort not possible\n");
    } else {
        for (int i = 0; i < cnt; ++i) {
            printf("%d", order[i]);
            if (i + 1 < cnt) putchar(' ');
        }
        putchar('\n');
    }

    // cleanup
    for (int i = 0; i < n; ++i) vec_free(&adj[i]);
    free(adj);
    free(indeg);
    free(q);
    free(order);
}