CC = g++
CFLAGS = -g -Wall

delist_test: delist.o delist_test.o
	$(CC) $(CFLAGS) $^ -o $@

delist_test.o: delist_test.cpp delist.h
	$(CC) $(CFLAGS) -c $<

delist.o: delist.cpp delist.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f delist_test *.o *~
