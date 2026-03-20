#ifndef DOUBLY_CIRCULAR_QUEUE_H
#define DOUBLY_CIRCULAR_QUEUE_H

typedef struct node *link;
struct node
{
    int data;
    link prev, next;
};

link make_node(int data);
void free_node(link p);
link search(int key);
void insert(link p); // 头插到 head 之后
void delete(link p); // 从链表中移除指定结点（不释放）
void traverse(void (*visit)(link));
void destroy(void); // 清空链表并释放所有结点

#endif // DOUBLY_CIRCULAR_QUEUE_H
