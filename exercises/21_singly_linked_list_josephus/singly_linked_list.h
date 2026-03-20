#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

// 通用单链表实现

// 定义链表节点结构
struct node {
    unsigned char item;  // 节点数据项
    struct node *next;   // 指向下一个节点的指针
};

// 定义指向节点的指针类型
typedef struct node *link;

// 创建新节点
link make_node(unsigned char item);

// 释放节点内存
void free_node(link p);

// 查找节点
link search(unsigned char key);

// 插入节点
void insert(link p);

// 删除指定节点
void delete(link p);

// 遍历链表
void traverse(void (*visit)(link));

// 销毁整个链表
void destroy(void);

// 在链表头部推入节点
void push(link p);

// 从链表头部弹出节点
link pop(void);

// 释放链表内存
void free_list(link head);

#endif  // SINGLY_LINKED_LIST_H
