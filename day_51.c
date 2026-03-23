#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    
    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    } else if (val > root->val) {
        root->right = insertIntoBST(root->right, val);
    }
    
    return root;
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, int p, int q) {
    if (root == NULL) {
        return NULL;
    }
    
    if (root->val > p && root->val > q) {
        return lowestCommonAncestor(root->left, p, q);
    } else if (root->val < p && root->val < q) {
        return lowestCommonAncestor(root->right, p, q);
    } else {
        return root;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    struct TreeNode* root = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        root = insertIntoBST(root, val);
    }

    int p, q;
    if (scanf("%d %d", &p, &q) == 2) {
        struct TreeNode* lca = lowestCommonAncestor(root, p, q);
        if (lca != NULL) {
            printf("%d\n", lca->val);
        }
    }

    return 0;
}