#ifndef EXERCISE_18_MYWC_H
#define EXERCISE_18_MYWC_H

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LEN 128
#define HASH_SIZE 1000

typedef struct WordCount {
    char word[MAX_WORD_LEN];
    int count;
    struct WordCount *next;
} WordCount;

void process_file(const char *filename);
WordCount **wc_create_hash_table();
unsigned int hash(const char *word);
void add_word(WordCount **hash_table, const char *word);
void print_word_counts(WordCount **hash_table);
void wc_free_hash_table(WordCount **hash_table);
bool is_valid_word_char(char c);
char to_lower(char c);

#endif //! EXERCISE_18_MYWC_H
