#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct { int u, v; long long w; } Edge;

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Expected: n m\n");
        return 1;
    }
    // If input vertices are 1-based, subtract 1 from u,v when reading edges.

    Edge *edges = malloc(sizeof(Edge) * m);
    if (!edges) return 1;
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        if (scanf("%d %d %lld", &u, &v, &w) != 3) {
            fprintf(stderr, "Expected m edges (u v w)\n");
            free(edges);
            return 1;
        }
        if (u < 0 || u >= n || v < 0 || v >= n) {
            fprintf(stderr, "Edge (%d,%d) out of bounds for n=%d\n", u, v, n);
            free(edges);
            return 1;
        }
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
    }

    const long long INF = LLONG_MAX / 4;
    long long *dist = malloc(sizeof(long long) * n);
    if (!dist) { free(edges); return 1; }
    for (int i = 0; i < n; ++i) dist[i] = INF;
    dist[0] = 0; // source = 0

    // relax edges n-1 times
    for (int it = 0; it < n - 1; ++it) {
        int changed = 0;
        for (int i = 0; i < m; ++i) {
            int u = edges[i].u, v = edges[i].v;
            long long w = edges[i].w;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                changed = 1;
            }
        }
        if (!changed) break;
    }

    // check for negative cycle
    for (int i = 0; i < m; ++i) {
        int u = edges[i].u, v = edges[i].v;
        long long w = edges[i].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("NEGATIVE CYCLE\n");
            free(edges);
            free(dist);
            return 0;
        }
    }

    // print distances (INF for unreachable)
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) printf("INF");
        else printf("%lld", dist[i]);
        if (i + 1 < n) putchar(' ');
    }
    putchar('\n');

    free(edges);
    free(dist);
    return 0;
}