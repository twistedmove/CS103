# Name: Mark Redekopp
# email: redekopp@usc.edu

CC = g++
CFLAGS = -g -Wall
CXXFLAGS = $(CFLAGS)
LDFLAGS =
SRCS = 	


all: maze

maze_io.o:  maze_io.cpp maze_io.h
	$(CC) $(CFLAGS) -c $<

maze: maze.cpp maze_io.o
	$(CC) $(CFLAGS) -o maze maze_io.o $<

clean:
	rm -f maze *.o *~