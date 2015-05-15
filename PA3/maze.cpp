#include <iostream>
#include "maze_io.h"
using namespace std;

// Prototypes
int maze_search(char **, int, int);
bool checkCell(int, int, int, int, bool **, char **,
               int *, int (*)[2], int *, int);

int main(int argc, char *argv[])
{
  int rows, cols, result;
  char **mymaze;

  if(argc < 3){
    cerr << "Usage: ./maze in_filename out_filename" << endl;
    return 1;
  }

  mymaze = read_maze(argv[1], &rows, &cols);

  // Exits the program if read_maze was unable to open the file or read the
  //  dimensions
  if(mymaze == NULL)
    return 1;

  // Attempts to find the shortest maze path and mark it with stars
  // If successful result will be 1
  result = maze_search(mymaze, rows, cols);

  if( result == 1 ){
    cout << "Path successfully found!" << endl;
    print_maze(mymaze,rows,cols);
    write_maze(argv[2],mymaze,rows,cols);
  }
  else if (result == 0) {
    cout << "No path could be found!" << endl;
  }
  else {
    cout << "Error occurred during search!" << endl;
  }

  // Deallocation of maze array here
  for(int i=0; i < rows; i++)
    delete [] mymaze[i];
  delete [] mymaze;

  return 0;
}



/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if an error occurred (no start of finish
 *     cell present in the maze)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char **maze, int rows, int cols)
{
  int head = -1, tail = 0, endsFound = 0;
  bool finished = false;

  // Declares a 2D bool array of the same size as the maze to remember when a
  //  cell is visited
  bool **visited = new bool *[rows];
  for(int i=0; i < rows; i++)
  {
    visited[i] = new bool[cols];

    // Initializes visited array to false
    for(int j=0; j < cols; j++)
      visited[i][j] = false;
  }

  // Declares the breadth-first search queue
  int (*queue)[2] = new int[rows*cols][2];

  // Declares a predecessor array to remember which cell lead to which and sets
  //  the first element to the head index
  int *predecessor = new int[rows*cols];
  predecessor[tail] = head;

  // Searches the maze for a start and end
  for(int i=0; i < rows; i++)
  {
    for(int j=0; j < cols; j++)
    {
      // Marks each start found
      if(maze[i][j]=='S')
      {
        // Adds the start location to the queue and increments the tail index
        queue[head+1][0] = i;
        queue[head+1][1] = j;
        tail++;

        // Marks the start point as visited
        visited[i][j] = true;
      }
      // Marks each end found
      else if(maze[i][j]=='F')
        endsFound++;

      // Warns that the maze contains a character that is not a
      //  'S','F','.',or '#'
      else if(maze[i][j]!='.' && maze[i][j]!='#')
      {
        cout << "Warning: unexpected character '" << maze[i][j] << 
                "' found." << endl;
      }
    }
  }

  // Provides error warnings for 0 or extra starts
  if(tail > 1)
  {
    cerr << "Error: multiple starts('S') found." << endl;

    // Deallocates the dynamic queue, predecessor, and visited arrays before
    //  exiting
    for(int i=0; i < rows; i++)
      delete [] visited[i];
    delete [] visited;
    delete [] queue;
    delete [] predecessor;
    
    return -1;
  }
  else if(tail < 1)
  {
    cerr << "Error: no start('S') found." << endl;

    // Deallocates the dynamic queue, predecessor, and visited arrays before
    //  exiting
    for(int i=0; i < rows; i++)
      delete [] visited[i];
    delete [] visited;
    delete [] queue;
    delete [] predecessor;

    return -1;
  }

  // Provides error warnings for 0 or extra ends
  if(endsFound > 1)
  {
    cerr << "Error: multiple ends('F') found." << endl;

    // Deallocates the dynamic queue, predecessor, and visited arrays before
    //  exiting
    for(int i=0; i < rows; i++)
      delete [] visited[i];
    delete [] visited;
    delete [] queue;
    delete [] predecessor;

    return -1;
  }
  else if(endsFound < 1)
  {
    cerr << "Error: no end('F') found." << endl;

    // Deallocates the dynamic queue, predecessor, and visited arrays before
    //  exiting
    for(int i=0; i < rows; i++)
      delete [] visited[i];
    delete [] visited;
    delete [] queue;
    delete [] predecessor;

    return -1;
  }

  // Looks for the shortest path
  while(tail > head)
  {
    // Moves the head index forward to "remove" an item from the list
    head++;
   
    // Checks the north neigbor cell and ends the search if the end is found
    finished = checkCell(queue[head][0]-1, rows, queue[head][1], cols, visited,
                         maze, predecessor, queue, &tail, head);
    if(finished)
      break;
    // Checks the west neighbor cell and ends the search if the end is found
    finished = checkCell(queue[head][0], rows, queue[head][1]-1, cols, visited,
                         maze, predecessor, queue, &tail, head);
    if(finished)
      break;
    // Checks the south neighbor cell and ends the search if the end is found
    finished = checkCell(queue[head][0]+1, rows, queue[head][1], cols, visited,
                         maze, predecessor, queue, &tail, head);
    if(finished)
      break;
    // Checks the east neighbor cell and ends the search if the end is found
    finished = checkCell(queue[head][0], rows, queue[head][1]+1, cols, visited,
                         maze, predecessor, queue, &tail, head);
    if(finished)
      break;
  }

  // If the queue is empty(head and tail indices are at the same spot) no path
  //  exists
  if(tail <= head)
  {
    // Deallocates the dynamic queue, predecessor, and visited arrays before
    //  exiting
    for(int i=0; i < rows; i++)
      delete [] visited[i];
    delete [] visited;
    delete [] queue;
    delete [] predecessor;

    return 0;
  }
  // If a path was found, fill it with stars
  else
  {
    // Walk back through the predecessor array starting at the last spot
    //  filled(tail index -1) until the array points to the first queue
    //  index(0) where the S is to avoid replacing it 
    for(int i=tail; predecessor[i] > 0; i = predecessor[i])
      maze[queue[predecessor[i]][0]][queue[predecessor[i]][1]] = '*';

    // Deallocates the dynamic queue, predecessor, and visited arrays before
    //  exiting
    for(int i=0; i < rows; i++)
      delete [] visited[i];
    delete [] visited;
    delete [] queue;
    delete [] predecessor;

    return 1;
  }
}

/**************************************************
 * Processes a neighboring cell:
 *   Marks new cells as found
 *   If the cell has a '.':
 *     adds the cell to the queue
 *     remembers the location of its predecessor
 *   If the cell has a 'F':
 *     marks the end as found
 *************************************************/
bool checkCell(int row, int maxRows, int col, int maxCols,
               bool **visited, char **maze, int *predecessor,
               int (*queue)[2], int *tail, int head)
{
  // Check that cell is in bounds
  if(row >= 0 && row < maxRows && col >= 0 && col < maxCols)
  {
    // If the cell has not been visited
    if(!visited[row][col])
    {
      // Marks the cell as visited
      visited[row][col] = true;

      // If the cell is a '.'
      if(maze[row][col] == '.')
      {
        // Remembers the predecessor cell by the head index
        predecessor[*tail] = head;

        // Adds the cell to the queue and increments the tail index
        queue[*tail][0] = row;
        queue[*tail][1] = col;
        (*tail)++;

        return false;
      }
    
      // If the north cell is an 'F'
      else if(maze[row][col] == 'F')
      {
        // Remembers the predecessor cell by the head index
        predecessor[*tail] = head;
        // Marks the end as found
        return true;
      }
      else
        return false;
    }
    else
      return false;
  }
  else
    return false;
}
