#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

static Node *new_node(int v) {
    Node *n = malloc(sizeof(*n));
    if (!n) return NULL;
    n->val = v;
    n->left = n->right = NULL;
    return n;
}

static void free_tree(Node *r) {
    if (!r) return;
    free_tree(r->left);
    free_tree(r->right);
    free(r);
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    if (N <= 0) {
        printf("\n");
        return 0;
    }

    int *arr = malloc(sizeof(int) * N);
    if (!arr) return 0;
    for (int i = 0; i < N; ++i) {
        if (scanf("%d", &arr[i]) != 1) { free(arr); return 0; }
    }

    Node **nodes = calloc(N, sizeof(Node*));
    if (!nodes) { free(arr); return 0; }

    for (int i = 0; i < N; ++i) {
        if (arr[i] != -1) nodes[i] = new_node(arr[i]);
        else nodes[i] = NULL;
    }

    for (int i = 0; i < N; ++i) {
        if (!nodes[i]) continue;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < N) nodes[i]->left = nodes[l];
        if (r < N) nodes[i]->right = nodes[r];
    }

    Node *root = nodes[0];
    if (!root) {
        printf("\n");
        free(nodes);
        free(arr);
        return 0;
    }

    /* buckets indexed by hd + offset, range [-N..N] */
    int B = 2 * N + 1;
    int offset = N;
    int **buckets = calloc(B, sizeof(int*));
    int *counts = calloc(B, sizeof(int));
    int *caps = calloc(B, sizeof(int));
    if (!buckets || !counts || !caps) {
        free(nodes); free(arr);
        free(buckets); free(counts); free(caps);
        return 0;
    }

    /* BFS queue storing node pointers and their horizontal distance */
    Node **q = malloc(sizeof(Node*) * N);
    int *hdq = malloc(sizeof(int) * N);
    if (!q || !hdq) {
        free(nodes); free(arr);
        free(buckets); free(counts); free(caps);
        free(q); free(hdq);
        return 0;
    }
    int head = 0, tail = 0;
    q[tail] = root; hdq[tail] = 0; ++tail;
    int minhd = 0, maxhd = 0;

    while (head < tail) {
        Node *cur = q[head];
        int hd = hdq[head];
        ++head;

        int idx = hd + offset;
        if (idx < 0 || idx >= B) {
            /* should not happen with bounds chosen, but guard */
            continue;
        }
        if (counts[idx] == caps[idx]) {
            int newcap = caps[idx] == 0 ? 4 : caps[idx] * 2;
            int *p = realloc(buckets[idx], sizeof(int) * newcap);
            if (!p) { /* abort on allocation failure */ break; }
            buckets[idx] = p;
            caps[idx] = newcap;
        }
        buckets[idx][counts[idx]++] = cur->val;
        if (hd < minhd) minhd = hd;
        if (hd > maxhd) maxhd = hd;

        if (cur->left) {
            q[tail] = cur->left;
            hdq[tail] = hd - 1;
            ++tail;
        }
        if (cur->right) {
            q[tail] = cur->right;
            hdq[tail] = hd + 1;
            ++tail;
        }
    }

    /* print columns from minhd to maxhd */
    for (int h = minhd; h <= maxhd; ++h) {
        int idx = h + offset;
        if (counts[idx] == 0) {
            printf("\n");
            continue;
        }
        for (int j = 0; j < counts[idx]; ++j) {
            if (j) printf(" ");
            printf("%d", buckets[idx][j]);
        }
        printf("\n");
    }

    /* cleanup */
    for (int i = 0; i < B; ++i) free(buckets[i]);
    free(buckets);
    free(counts);
    free(caps);
    free(q);
    free(hdq);

    if (root) free_tree(root);
    free(nodes);