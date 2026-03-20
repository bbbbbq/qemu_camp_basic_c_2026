#ifndef SIMPLE_TREE_H
#define SIMPLE_TREE_H

#include <stdbool.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct QueueNode {
    TreeNode *tree_node;
    struct QueueNode *next;
} QueueNode;

// 队列结构
typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

Queue* create_queue();
void enqueue(Queue *q, TreeNode *tree_node);
TreeNode* dequeue(Queue *q);
bool is_empty(Queue *q);
void free_queue(Queue *q);

TreeNode* build_tree_by_level(int *level_order, int size);
void preorder_traversal(TreeNode *root);
void preorder_traversal_iterative(TreeNode *root);
void free_tree(TreeNode *root);

#endif //!SIMPLE_QUEUE_H