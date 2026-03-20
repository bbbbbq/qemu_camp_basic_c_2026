#include <stdio.h>

unsigned int gcd_asm(unsigned int a, unsigned int b) {
    unsigned int result;
    
    // TODO: 替换下方的TODO段
    // I AM NOT DONE
    __asm__ volatile (
        "mov %1, %%eax\n\t"     // 将a存入eax
        "mov %2, %%ebx\n\t"     // 将b存入ebx
        "jmp .L_check\n\t"      // 跳转到检查条件
        
        ".L_loop:\n\t"
        "   TODO\n\t"
        
        ".L_check:\n\t"
        "   test TODO\n\t"      // 测试ebx是否为0
        "   jne .L_loop\n\t"    // 如果不为0，继续循环
        
        "mov %%eax, %0"         // 将结果（eax）存入输出变量
        : "=r" (TODO)           // 输出操作数
        : "r" (TODO), "r" (TODO)      // 输入操作数
        : "TODO", "TODO", "TODO" // 被修改的寄存器
    );
    
    return result;
}

int main(int argc, char* argv[]) {
    printf("%d\n", gcd_asm(12, 8));
    printf("%d\n", gcd_asm(7, 5));
    return 0;
}