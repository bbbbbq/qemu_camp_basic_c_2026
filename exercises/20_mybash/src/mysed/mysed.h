#ifndef MYSED_H
#define MYSED_H

#include <stdio.h>

#include "common.h"

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str);
void replace_first_occurrence(char* str, const char* old, const char* new);

#endif //! MYSED_H