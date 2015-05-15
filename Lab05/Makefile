# Name: Mark Redekopp
# email: redekopp@usc.edu

CC = g++
CFLAGS = -g -Wall
LDFLAGS =
SRCS =  lab5.cpp bmplib.cpp
OBJ = $(SRCS:.cpp=.o)
DEMOSRC = demo.cpp bmplib.cpp
DEMOOBJ = $(DEMOSRC:.cpp=.o)



all: lab5 demo

demo: $(DEMOOBJ)
	$(CC) $(CFLAGS) $(DEMOOBJ) -o demo
lab5: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o lab5

.cpp.o:
	$(CC) $(CFLAGS) -c $<

bmplib.o : bmplib.h

clean:
	rm -f *.o lab5 *~

