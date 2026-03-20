#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 16 LRU 缓存淘汰算法（哈希表 + 双向链表）
 *  - put(k,v)、get(k) 均为 O(1)
 *  - 容量满时淘汰最久未使用（LRU）的元素
 */

typedef struct LRUNode {
    int key;
    int value;
    struct LRUNode* prev;
    struct LRUNode* next;
} LRUNode;

typedef struct HashEntry {
    int key;
    LRUNode* node;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    int capacity;
    int size;
    LRUNode* head; /* 最近使用（MRU） */
    LRUNode* tail; /* 最久未使用（LRU） */
    /* 简单链式哈希表 */
    size_t bucket_count;
    HashEntry** buckets;
} LRUCache;

static unsigned hash_int(int key) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

static HashEntry* hash_find(LRUCache* c, int key, HashEntry*** pprev_next) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

static void list_add_to_head(LRUCache* c, LRUNode* node) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

static void list_remove(LRUCache* c, LRUNode* node) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

static void list_move_to_head(LRUCache* c, LRUNode* node) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

static LRUNode* list_pop_tail(LRUCache* c) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

/* LRU 接口实现 */
static LRUCache* lru_create(int capacity) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

static void lru_free(LRUCache* c) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

static int lru_get(LRUCache* c, int key, int* out_value) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

static void lru_put(LRUCache* c, int key, int value) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

/* 打印当前缓存内容（从头到尾） */
static void lru_print(LRUCache* c) {
    LRUNode* p = c->head;
    int first = 1;
    while (p) {
        if (!first) printf(", ");
        first = 0;
        printf("%d:%d", p->key, p->value);
        p = p->next;
    }
    printf("\n");
}

int main(void) {
    /* 容量 3：put(1,1), put(2,2), put(3,3), put(4,4), get(2), put(5,5) */
    LRUCache* c = lru_create(3);
    if (!c) {
        fprintf(stderr, "创建 LRU 失败\n");
        return 1;
    }

    lru_put(c, 1, 1); /* 缓存：1 */
    lru_put(c, 2, 2); /* 缓存：2,1 */
    lru_put(c, 3, 3); /* 缓存：3,2,1 (满) */
    lru_put(c, 4, 4); /* 淘汰 LRU(1)，缓存：4,3,2 */

    int val;
    if (lru_get(c, 2, &val)) {
        /* 访问 2：缓存：2,4,3 */
        (void)val; /* 演示无需使用 */
    }

    lru_put(c, 5, 5); /* 淘汰 LRU(3)，缓存：5,2,4 */

    /* 期望最终键集合：{2,4,5}，顺序无关。此处按最近->最久打印：5:5, 2:2, 4:4 */
    lru_print(c);

    lru_free(c);
    return 0;
}
