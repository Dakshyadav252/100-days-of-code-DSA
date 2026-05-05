#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct { int to; long long w; } Edge;
typedef struct {
    Edge *data;
    int size;
    int cap;
} EdgeVec;

void vec_init(EdgeVec *v) {
    v->cap = 4;
    v->size = 0;
    v->data = malloc(sizeof(Edge) * v->cap);
}

void vec_push(EdgeVec *v, Edge e) {
    if (v->size == v->cap) {
        v->cap *= 2;
        v->data = realloc(v->data, sizeof(Edge) * v->cap);
    }
    v->data[v->size++] = e;
}

void vec_free(EdgeVec *v) {
    free(v->data);
}

/* simple min-heap of (dist, vertex) */
typedef struct { long long d; int v; } HNode;
typedef struct {
    HNode *a;
    int size;
    int cap;
} MinHeap;

void heap_init(MinHeap *h) {
    h->cap = 8;
    h->size = 0;
    h->a = malloc(sizeof(HNode) * h->cap);
}

void heap_push(MinHeap *h, HNode x) {
    if (h->size == h->cap) {
        h->cap *= 2;
        h->a = realloc(h->a, sizeof(HNode) * h->cap);
    }
    int i = h->size++;
    h->a[i] = x;
    while (i > 0) {
        int p = (i - 1) >> 1;
        if (h->a[p].d <= h->a[i].d) break;
        HNode tmp = h->a[p]; h->a[p] = h->a[i]; h->a[i] = tmp;
        i = p;
    }
}

int heap_empty(MinHeap *h) { return h->size == 0; }

HNode heap_pop(MinHeap *h) {
    HNode res = h->a[0];
    h->a[0] = h->a[--h->size];
    int i = 0;
    while (1) {
        int l = i * 2 + 1, r = l + 1, smallest = i;
        if (l < h->size && h->a[l].d < h->a[smallest].d) smallest = l;
        if (r < h->size && h->a[r].d < h->a[smallest].d) smallest = r;
        if (smallest == i) break;
        HNode tmp = h->a[i]; h->a[i] = h->a[smallest]; h->a[smallest] = tmp;
        i = smallest;
    }
    return res;
}

int main(void) {
    int n, m, s;
    if (scanf("%d %d %d", &n, &m, &s) != 3) {
        fprintf(stderr, "Expected: n m s\n");
        return 1;
    }
    // if input vertices are 1-based, uncomment: --s; and subtract 1 from u,v when reading edges.

    EdgeVec *adj = malloc(sizeof(EdgeVec) * n);
    for (int i = 0; i < n; ++i) vec_init(&adj[i]);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        if (scanf("%d %d %lld", &u, &v, &w) != 3) {
            fprintf(stderr, "Expected m weighted edges (u v w)\n");
            return 1;
        }
        if (u < 0 || u >= n || v < 0 || v >= n) {
            fprintf(stderr, "Edge (%d,%d) out of bounds for n=%d\n", u, v, n);
            return 1;
        }
        vec_push(&adj[u], (Edge){v, w});
    }

    long long INF = LLONG_MAX / 4;
    long long *dist = malloc(sizeof(long long) * n);
    for (int i = 0; i < n; ++i) dist[i] = INF;
    dist[s] = 0;

    MinHeap pq;
    heap_init(&pq);
    heap_push(&pq, (HNode){0, s});

    while (!heap_empty(&pq)) {
        HNode cur = heap_pop(&pq);
        long long d = cur.d;
        int u = cur.v;
        if (d != dist[u]) continue; // stale entry
        for (int k = 0; k < adj[u].size; ++k) {
            Edge e = adj[u].data[k];
            if (e.w < 0) {
                fprintf(stderr, "Negative weight detected; Dijkstra requires non-negative edges\n");
                return 1;
            }
            if (dist[e.to] > d + e.w) {
                dist[e.to] = d + e.w;
                heap_push(&pq, (HNode){dist[e.to], e.to});
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) printf("-1");
        else printf("%lld", dist[i]);
        if (i + 1 < n) putchar(' ');
    }
    putchar('\n');

    for (int i = 0; i < n; ++i) vec_free(&adj[i]);
    free(adj);
    free(dist);
    free(pq.a);