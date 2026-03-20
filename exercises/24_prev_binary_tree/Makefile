CC = gcc
CPPFLAGS ?=
CPPFLAGS += -MMD -MP
CFLAGS = -Wall -g -O2
LDFLAGS =
LDLIBS =

TARGET = 24_prev_binary_tree
SRC = 24_prev_binary_tree.c simple_tree.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

.PHONY: all clean run rebuild debug

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

run: all
	@./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ) $(DEP)

rebuild: clean all

debug: CFLAGS += -g -O0
debug: clean all

-include $(DEP)
