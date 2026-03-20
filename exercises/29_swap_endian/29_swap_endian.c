#include <stdint.h>
#include <stdio.h>

uint32_t swap_endian(uint32_t num) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
}

int main(int argc, char* argv[]) {
    uint32_t num = 0x78563412;
    uint32_t swapped = swap_endian(num);
    printf("0x%08x -> 0x%08x\n", num, swapped);
    return 0;
}