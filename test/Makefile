CC = clang++

ARGS = -std=c++20 -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -g

all: clean ll lld stack queue smartll

ll: test_linked_list.cpp
	$(CC) $^ $(ARGS) -o "$@"

lld: test_doubly_linked_list.cpp
	$(CC) $^ $(ARGS) -o "$@"

stack: test_stack.cpp
	$(CC) $^ $(ARGS) -o "$@"

queue: test_queue.cpp
	$(CC) $^ $(ARGS) -o "$@"

smartll: test_smart_linked_list.cpp
	$(CC) $^ $(ARGS) -o "$@"

clean:
	rm -f ll lld stack queue smartll
