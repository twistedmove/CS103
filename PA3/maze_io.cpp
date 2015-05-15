#include <iostream>
#include <fstream>
#include "maze_io.h"

using namespace std;

/*************************************************
 * Opens the file specified by filename, and reads
 *  the maze into a dynamically allocated array.
 *
 * Returns the pointer to that array (deleted in main()
 *  ).  Return NULL if unable to open the file or
 *  can't read the dimensions.
 *
 * We also pass in two pointers to integers. Fill 
 *  the integers pointed to by these arguments
 *  with the number of rows and columns 
 *  read by from the file (first two value
 *  in the file)
 *************************************************/

char ** read_maze(char *filename, int *rows, int *cols )
{
  // Opens the maze file and returns NULL pointer if unsuccessful
  ifstream mazeFile(filename);
  if(mazeFile.fail())
  {
    cout << "Unable to open file: " << filename << endl;
    return NULL;
  }

  // Reads in two integers as the dimensions and returns NULL
  //  pointer if unsuccessful
  mazeFile >> *rows >> *cols;
  if(mazeFile.fail())
  {
    cout << "Unable to read maze dimensions." << endl;
    return NULL;
  }

  // Dynamically allocates a 2D array of chars and fills it with the maze
  char **maze = new char*[*rows];
  for(int i=0; i < *rows; i++)
  {
    maze[i] = new char[*cols];

    for(int j=0; j < *cols; j++)
      mazeFile >> maze[i][j];
  }

  // Closes the maze file
  mazeFile.close();

  return maze; 
}

/*************************************************
 * Print the maze dimensions and contents in a 2D 
 *  format to the screen
 *************************************************/
void print_maze(char **maze, int rows, int cols)
{
  cout << rows << " " << cols << endl;

  for(int i=0; i < rows; i++)
  {
    for(int j=0; j < cols; j++)
      cout << maze[i][j];
  
    cout << endl;
  }
}

/*************************************************
 * Opens the file specified by filename and writes
 *  the contents of the maze array to the file with
 *  the dimensions on the first line.
 *************************************************/
void write_maze(char *filename, char **maze, int rows, int cols)
{
  ofstream solvedMazeFile(filename);

  solvedMazeFile << rows << " " << cols << endl;

  for(int i=0; i < rows; i++)
  {
    for(int j=0; j < cols; j++)
      solvedMazeFile << maze[i][j];

    solvedMazeFile << endl;
  }

  // Closes the output file when done
  solvedMazeFile.close();
}
