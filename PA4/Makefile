# Name: Mark Redekopp
# email: redekopp@usc.edu

CC = g++
CFLAGS = -g -Wall
LDFLAGS =


all : user.o network.o social_network.o
	@echo "social_network"
	@echo "Compiling and linking"
	$(CC) $(CFLAGS) user.o network.o social_network.o -o social_network

user.o : user.h user.cpp
	$(CC) $(CFLAGS) -c user.cpp

network.o : network.h user.h network.cpp
	$(CC) $(CFLAGS) -c network.cpp

social_network.o : network.h user.h social_network.cpp
	$(CC) $(CFLAGS) -c social_network.cpp


clean:
	rm -f social_network *.o *~