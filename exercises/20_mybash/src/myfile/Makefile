# src/myfile/Makefile

CC = gcc
CFLAGS = -Wall -I../../include -g -fPIE

# 库名称
LIBNAME := myfile
# 静态库输出名：libmyfile.a
LIB := lib$(LIBNAME).a
# 最终库输出目录（比如 ./obj/src/myfile/）
OBJDIR ?= ./obj
# 最终 .a 文件路径
LIB_PATH := $(OBJDIR)/$(LIB)

# 源文件
SRCS := myfile.c
OBJS := $(SRCS:.c=.o)
OBJS := $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))

all: $(LIB_PATH)

# TODO: 在这里添加你的代码
# I AM NOT DONE

clean:
	@rm -rf $(OBJDIR)/*.o $(LIB_PATH)