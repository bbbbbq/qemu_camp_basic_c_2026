#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

// 环形单链表节点
typedef struct Node {
    int id;             // 节点编号（1..n）
    struct Node* next;  // 指向下一个节点
} Node;

// 构建包含 n 个节点的环形链表（1..n），尾节点 next 指向头节点
Node* create_circular_list(int n);

// 释放环形链表
void free_list(Node* head);

#endif  // CIRCULAR_LINKED_LIST_H
