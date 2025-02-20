CC = clang++

ARGS = -std=c++20 -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -g

all: test

test: main.cpp
	$(CC) $^ $(ARGS) -o "$@"

clean:
	rm -f test
