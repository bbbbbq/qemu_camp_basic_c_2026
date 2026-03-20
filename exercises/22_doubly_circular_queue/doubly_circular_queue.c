#include "doubly_circular_queue.h"

#include <stdlib.h>

// 头尾哨兵
static struct node tailsentinel;
static struct node headsentinel = {0, NULL, &tailsentinel};
static struct node tailsentinel = {0, &headsentinel, NULL};

static link head = &headsentinel;
static link tail = &tailsentinel;

link make_node(int data) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

void free_node(link p) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

link search(int key) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

void insert(link p) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

void delete(link p) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

void traverse(void (*visit)(link)) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

void destroy(void) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}
