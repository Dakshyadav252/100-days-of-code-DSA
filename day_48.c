#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int countLeaves(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    
    return countLeaves(root->left) + countLeaves(root->right);
}