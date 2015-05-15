#ifndef MAZE_IO_H
#define MAZE_IO_H

char ** read_maze(char *filename, int *rows, int *cols );
void print_maze(char **maze, int rows, int cols);
void write_maze(char *filename, char **maze, int rows, int cols);

#endif
