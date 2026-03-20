# src/mybash/Makefile

CC = gcc
CFLAGS = -Wall -I../../include

# 可执行文件名
TARGET := mybash
# 最终输出到 BINDIR（比如 ./bin/）
BINDIR ?= ./bin
# 中间文件目录（比如 ./obj/src/mybash/）
OBJDIR ?= ./obj
LINKLIBS ?= -L../../obj/mysed -L../../obj/mywc -L../../obj/mytrans -L../../obj/myfile

# 源文件
SRCS := main.c
OBJS := $(SRCS:.c=.o)
OBJS := $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))

# 最终二进制路径
TARGET_PATH := $(BINDIR)/$(TARGET)

all: $(TARGET_PATH)

# TODO: 在这里添加你的代码
# I AM NOT DONE

clean:
	@rm -rf $(OBJDIR)/*.o $(TARGET_PATH)