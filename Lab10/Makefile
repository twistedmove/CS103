CC = g++
CFLAGS = -g -Wall
ALL = bigint.o test0 test1 copies fib 2pow fact

all: $(ALL)

bigint.o: bigint.cpp bigint.h
	$(CC) $(CFLAGS) -c $< -o $@

test0: bigint.o test0.cpp
	$(CC) $(CFLAGS) $^ -o $@

test1: bigint.o test1.cpp
	$(CC) $(CFLAGS) $^ -o $@

copies: bigint.o copies.cpp
	$(CC) $(CFLAGS) $^ -o $@

fib: bigint.o fib.cpp
	$(CC) $(CFLAGS) $^ -o $@

2pow: bigint.o 2pow.cpp
	$(CC) $(CFLAGS) $^ -o $@

fact: bigint.o fact.cpp
	$(CC) $(CFLAGS) $^ -o $@

bases: bigint.o bases.cpp
	$(CC) $(CFLAGS) $^ -o $@

badaccess: bigint.o badaccess.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(ALL) badaccess

bigint.tar:
	rm -f bigint.tar
	tar cvf bigint.tar Makefile bigint.h test0.cpp test1.cpp copies.cpp \
                fib.cpp 2pow.cpp fact.cpp bases.cpp
