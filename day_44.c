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

static void inorder(Node *r, int *first) {
    if (!r) return;
    inorder(r->left, first);
    if (!*first) printf(" ");
    *first = 0;
    printf("%d", r->val);
    inorder(r->right, first);
}

static void preorder(Node *r, int *first) {
    if (!r) return;
    if (!*first) printf(" ");
    *first = 0;
    printf("%d", r->val);
    preorder(r->left, first);
    preorder(r->right, first);
}

static void postorder(Node *r, int *first) {
    if (!r) return;
    postorder(r->left, first);
    postorder(r->right, first);
    if (!*first) printf(" ");
    *first = 0;
    printf("%d", r->val);
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
        printf("\n\n\n");
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
        printf("\n\n\n");
    } else {
        int first;
        first = 1; inorder(root, &first); printf("\n");
        first = 1; preorder(root, &first); printf("\n");
        first = 1; postorder(root, &first); printf("\n");
    }

    if (root) free_tree(root);
    free(nodes);
    free(arr);
    return 0;
}