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

/* build tree from preorder[preL..preR) and inorder[inL..inR) */
static Node *build(int *pre, int preL, int preR, int *in, int inL, int inR) {
    if (preL >= preR || inL >= inR) return NULL;
    int rootVal = pre[preL];
    Node *root = new_node(rootVal);
    if (!root) return NULL;
    /* find rootVal in inorder range */
    int inIdx = inL;
    while (inIdx < inR && in[inIdx] != rootVal) ++inIdx;
    int leftSize = inIdx - inL;
    root->left = build(pre, preL + 1, preL + 1 + leftSize, in, inL, inIdx);
    root->right = build(pre, preL + 1 + leftSize, preR, in, inIdx + 1, inR);
    return root;
}

static void postorder_print(Node *r, int *first) {
    if (!r) return;
    postorder_print(r->left, first);
    postorder_print(r->right, first);
    if (!*first) printf(" ");
    *first = 0;
    printf("%d", r->val);
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    if (N <= 0) {
        printf("\n");
        return 0;
    }

    int *pre = malloc(sizeof(int) * N);
    int *in = malloc(sizeof(int) * N);
    if (!pre || !in) { free(pre); free(in); return 0; }

    for (int i = 0; i < N; ++i) {
        if (scanf("%d", &pre[i]) != 1) { free(pre); free(in); return 0; }
    }
    for (int i = 0; i < N; ++i) {
        if (scanf("%d", &in[i]) != 1) { free(pre); free(in); return 0; }
    }

    Node *root = build(pre, 0, N, in, 0, N);
    if (!root) {
        printf("\n");
        free(pre); free(in);
        return 0;
    }

    int first = 1;
    postorder_print(root, &first);
    printf("\n");

    free_tree(root);
    free(pre);
    free(in);
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

/* build tree from preorder[preL..preR) and inorder[inL..inR) */
static Node *build(int *pre, int preL, int preR, int *in, int inL, int inR) {
    if (preL >= preR || inL >= inR) return NULL;
    int rootVal = pre[preL];
    Node *root = new_node(rootVal);
    if (!root) return NULL;
    /* find rootVal in inorder range */
    int inIdx = inL;
    while (inIdx < inR && in[inIdx] != rootVal) ++inIdx;
    int leftSize = inIdx - inL;
    root->left = build(pre, preL + 1, preL + 1 + leftSize, in, inL, inIdx);
    root->right = build(pre, preL + 1 + leftSize, preR, in, inIdx + 1, inR);
    return root;
}

static void postorder_print(Node *r, int *first) {
    if (!r) return;
    postorder_print(r->left, first);
    postorder_print(r->right, first);
    if (!*first) printf(" ");
    *first = 0;
    printf("%d", r->val);
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    if (N <= 0) {
        printf("\n");
        return 0;
    }

    int *pre = malloc(sizeof(int) * N);
    int *in = malloc(sizeof(int) * N);
    if (!pre || !in) { free(pre); free(in); return 0; }

    for (int i = 0; i < N; ++i) {
        if (scanf("%d", &pre[i]) != 1) { free(pre); free(in); return 0; }
    }
    for (int i = 0; i < N; ++i) {
        if (scanf("%d", &in[i]) != 1) { free(pre); free(in); return 0; }
    }

    Node *root = build(pre, 0, N, in, 0, N);
    if (!root) {
        printf("\n");
        free(pre); free(in);
        return 0;
    }

    int first = 1;
    postorder_print(root, &first);
    printf("\n");

    free_tree(root);
    free(pre);
    free(in);
    return 0;