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

/* build tree from inorder[inL..inR) and postorder[postL..postR) */
static Node *build(int *in, int inL, int inR, int *post, int postL, int postR) {
    if (inL >= inR || postL >= postR) return NULL;
    int rootVal = post[postR - 1];
    Node *root = new_node(rootVal);
    if (!root) return NULL;
    /* find rootVal in inorder range */
    int idx = inL;
    while (idx < inR && in[idx] != rootVal) ++idx;
    int leftSize = idx - inL;
    root->left = build(in, inL, idx, post, postL, postL + leftSize);
    root->right = build(in, idx + 1, inR, post, postL + leftSize, postR - 1);
    return root;
}

static void preorder_print(Node *r, int *first) {
    if (!r) return;
    if (!*first) printf(" ");
    *first = 0;
    printf("%d", r->val);
    preorder_print(r->left, first);
    preorder_print(r->right, first);
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    if (N <= 0) {
        printf("\n");
        return 0;
    }

    int *in = malloc(sizeof(int) * N);
    int *post = malloc(sizeof(int) * N);
    if (!in || !post) { free(in); free(post); return 0; }

    for (int i = 0; i < N; ++i) {
        if (scanf("%d", &in[i]) != 1) { free(in); free(post); return 0; }
    }
    for (int i = 0; i < N; ++i) {
        if (scanf("%d", &post[i]) != 1) { free(in); free(post); return 0; }
    }

    Node *root = build(in, 0, N, post, 0, N);
    if (!root) {
        printf("\n");
        free(in); free(post);
        return 0;
    }

    int first = 1;
    preorder_print(root, &first);
    printf("\n");

    free_tree(root);
    free(in);