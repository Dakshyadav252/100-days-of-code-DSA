#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MinHeap {
    int *data;
    int size;
    int cap;
} MinHeap;

static MinHeap *heap_new(int cap) {
    MinHeap *h = malloc(sizeof(*h));
    if (!h) return NULL;
    h->data = malloc(sizeof(int) * (cap > 0 ? cap : 1));
    if (!h->data) { free(h); return NULL; }
    h->size = 0;
    h->cap = cap > 0 ? cap : 1;
    return h;
}

static void heap_free(MinHeap *h) {
    if (!h) return;
    free(h->data);
    free(h);
}

static void heap_swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

static int heap_grow(MinHeap *h) {
    int newcap = h->cap * 2;
    int *p = realloc(h->data, sizeof(int) * newcap);
    if (!p) return 0;
    h->data = p;
    h->cap = newcap;
    return 1;
}

static void heap_sift_up(MinHeap *h, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (h->data[parent] <= h->data[idx]) break;
        heap_swap(&h->data[parent], &h->data[idx]);
        idx = parent;
    }
}

static void heap_sift_down(MinHeap *h, int idx) {
    int n = h->size;
    while (1) {
        int l = idx * 2 + 1;
        int r = idx * 2 + 2;
        int smallest = idx;
        if (l < n && h->data[l] < h->data[smallest]) smallest = l;
        if (r < n && h->data[r] < h->data[smallest]) smallest = r;
        if (smallest == idx) break;
        heap_swap(&h->data[idx], &h->data[smallest]);
        idx = smallest;
    }
}

static int heap_insert(MinHeap *h, int v) {
    if (h->size == h->cap) {
        if (!heap_grow(h)) return 0;
    }
    h->data[h->size++] = v;
    heap_sift_up(h, h->size - 1);
    return 1;
}

static int heap_peek(MinHeap *h, int *out) {
    if (h->size == 0) return 0;
    *out = h->data[0];
    return 1;
}

static int heap_extract_min(MinHeap *h, int *out) {
    if (h->size == 0) return 0;
    *out = h->data[0];
    h->size--;
    if (h->size > 0) {
        h->data[0] = h->data[h->size];
        heap_sift_down(h, 0);
    }
    return 1;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    MinHeap *h = heap_new(N);
    if (!h) return 0;

    for (int i = 0; i < N; ++i) {
        char cmd[32];
        if (scanf("%31s", cmd) != 1) break;
        if (strcmp(cmd, "insert") == 0) {
            int x;
            if (scanf("%d", &x) != 1) break;
            heap_insert(h, x);
        } else if (strcmp(cmd, "peek") == 0) {
            int v;
            if (heap_peek(h, &v)) printf("%d\n", v);
            else printf("-1\n");
        } else if (strcmp(cmd, "extractMin") == 0) {
            int v;
            if (heap_extract_min(h, &v)) printf("%d\n", v);
            else printf("-1\n");
        } else {
            /* ignore rest of line for unknown command */
            char tmp[256];
            fgets(tmp, sizeof(tmp), stdin);
        }
    }

    heap_free(h);