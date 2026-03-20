#include "simple_tree.h"

#include <stdio.h>
#include <limits.h>

int main(int argc, char* argv[]) {
    int level_order1[] = {1, 2, 3, INT_MIN, INT_MIN, 4, 5};
    TreeNode* root = build_tree_by_level(level_order1, sizeof(level_order1) / sizeof(level_order1[0]));
    preorder_traversal(root);
    free_tree(root);
    printf("\n");

    int level_order2[] = {1, INT_MIN, 2, 3, 4, INT_MIN, 5};
    root = build_tree_by_level(level_order2, sizeof(level_order2) / sizeof(level_order2[0]));
    preorder_traversal_iterative(root);
    free_tree(root);
    printf("\n");
    return 0;
}