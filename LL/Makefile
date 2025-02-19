CC = clang++

ARGS = -std=c++20 -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -g

all: ll lldouble

ll lldouble: ll.cpp lldouble.cpp
	$(CC) "$@.cpp" $(ARGS) -o "$@"

clean:
	rm -f ll lldouble
