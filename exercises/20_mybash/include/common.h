#ifndef COMMON_H
#define COMMON_H

#define SYSCALL_CMD0(name) \
    extern int __cmd_##name(void);

#define SYSCALL_CMD1(name, arg1) \
    extern int __cmd_##name(arg1);

#define SYSCALL_CMD2(name, arg1, arg2) \
    extern int __cmd_##name(arg1, arg2);

SYSCALL_CMD1(mytrans, const char*);
SYSCALL_CMD1(myfile, const char*);
SYSCALL_CMD2(mysed, const char*, const char*);
SYSCALL_CMD1(mywc, const char*);

#endif //! COMMON_H