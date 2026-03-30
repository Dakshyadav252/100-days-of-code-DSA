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

    Node **q = malloc(sizeof(Node*) * N);
    if (!q) { free(nodes); free(arr); return 0; }
    int head = 0, tail = 0;
    q[tail++] = root;
    int first = 1;

    while (head < tail) {
        int level_size = tail - head;
        for (int i = 0; i < level_size; ++i) {
            Node *cur = q[head++];
            if (cur->left) q[tail++] = cur->left;
            if (cur->right) q[tail++] = cur->right;
            if (i == level_size - 1) {
                if (!first) printf(" ");
                first = 0;
                printf("%d", cur->val);
            }
        }
    }
    printf("\n");

    free(q);
    if (root) free_tree(root);
    free(nodes);
    free(arr);
    return 0;
}
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

    Node **q = malloc(sizeof(Node*) * N);
    if (!q) { free(nodes); free(arr); return 0; }
    int head = 0, tail = 0;
    q[tail++] = root;
    int first = 1;

    while (head < tail) {
        int level_size = tail - head;
        for (int i = 0; i < level_size; ++i) {
            Node *cur = q[head++];
            if (cur->left) q[tail++] = cur->left;
            if (cur->right) q[tail++] = cur->right;
            if (i == level_size - 1) {
                if (!first) printf(" ");
                first = 0;
                printf("%d", cur->val);
            }
        }
    }
    printf("\n");

    free(q);
    if (root) free_tree(root);
    free(nodes);
    free(arr);
    return 0;
