#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#ifdef TODO

#define DEBUG_PRINT(fmt, ...) 
    // TODO: 在这里添加你的代码
    // I AM NOT DONE

#else

#define DEBUG_PRINT(fmt, ...) do {} while (0)

#endif



























//! MUST BE ENSURE THE DEBUG_PRINT("x=%d", x) AT THE 48 LINE

// 测试代码
void test() {
    int x = 42;
    DEBUG_PRINT("x=%d", x);
}

int main() {
    test();
    return 0;
}