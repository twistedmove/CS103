CC = g++
CFLAGS = -g -Wall
ALL = bmplib3.o std_draw_test turtle.o threestep shape vanish

all: $(ALL)

bmplib3.o: bmplib3.cpp bmplib3.h
	$(CC) $(CFLAGS) -c $< -o $@
	
turtle.o: turtle.cpp turtle.h
	$(CC) $(CFLAGS) -c $< -o $@
	
std_draw_test: bmplib3.o std_draw_test.cpp
	$(CC) $(CFLAGS) $^ -o $@

threestep: bmplib3.o turtle.o threestep.cpp
	$(CC) $(CFLAGS) $^ -o $@

shape: bmplib3.o turtle.o shape.cpp
	$(CC) $(CFLAGS) $^ -o $@

vanish: bmplib3.o turtle.o vanish.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(ALL)

