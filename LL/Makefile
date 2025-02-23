CC = clang++

ARGS = -std=c++20 -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -g

all: clean ll lld

ll: test_linked_list.cpp
	$(CC) $^ $(ARGS) -o "$@"

lld: test_doubly_linked_list.cpp
	$(CC) $^ $(ARGS) -o "$@"

clean:
	rm -f ll lld
