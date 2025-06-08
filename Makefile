CFLAGS =-Wall -Wextra -ggdb
test: main.c
	$(CC) $(CFLAGS) -o main main.c queue.c stack.c binary_tree.c -lncurses