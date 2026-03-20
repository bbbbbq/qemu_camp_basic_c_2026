// hash_table.h
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>
#define HASH_TABLE_SIZE 10000003  // 应选一个较大的质数，有利于分布

// 哈希节点
typedef struct HashNode {
    char *key;              // 英文单词，如 "a", "a.m."
    char *value;            // 中文翻译，如 "art. 一;字母A"
    struct HashNode *next;  // 用于解决冲突（链地址法）
} HashNode;

// 哈希表
typedef struct {
    HashNode *buckets[HASH_TABLE_SIZE];
} HashTable;

// 函数声明
HashTable* create_hash_table();
void free_hash_table(HashTable *table);
int hash_table_insert(HashTable *table, const char *key, const char *value);
const char* hash_table_lookup(HashTable *table, const char *key);

int load_dictionary(const char *filename, HashTable *table, uint64_t* dict_count);

#endif
