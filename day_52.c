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

static Node *lca(Node *root, int a, int b) {
    if (!root) return NULL;
    if (root->val == a || root->val == b) return root;
    Node *L = lca(root->left, a, b);
    Node *R = lca(root->right, a, b);
    if (L && R) return root;
    return L ? L : R;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    if (N <= 0) { printf("\n"); return 0; }

    int *arr = malloc(sizeof(int) * N);
    if (!arr) return 0;