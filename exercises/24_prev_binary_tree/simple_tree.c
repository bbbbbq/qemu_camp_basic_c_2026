#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

TreeNode* dequeue(Queue *q) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

void preorder_traversal(TreeNode *root) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

void preorder_traversal_iterative(TreeNode *root) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
