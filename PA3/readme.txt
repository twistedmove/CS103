CSCI 103 Programming Assignment 3, Path-so-logical, Fall 2014

Name: Will Gauthier

Email Address: wgauthie@usc.edu

=============================== Prelab =======================================

I will use a dynamically allocated boolean 2D array that is the same size as
the maze to remember which locations have been used. It will be initialized to
false and set to true whenever a cell is visited.

I mark a cell as visited immediately after I check to see whether it is a 
valid, unvisited space.

================================== Review ===================================

My mymaze.txt test file is a 4x5 grid with the start at the top left, the end
at the bottom right, and no pound sign(#) walls.  All possible paths complete
the maze, and there are several shortest paths of the same length.  My program
finds a shortest path properly, and the one it finds is dependent upon the
algorithm checking the neighbor cells in the order: north, west, south, east.

================================ Remarks ====================================

Filling in anything here is OPTIONAL.

Approximately how long did you spend on this assignment?

:I spent about 7 hours working on this.

Were there any specific problems you encountered? This is especially useful to
know if you turned it in incomplete.

:The biggest chunks of time devoted to one task that I had on this lab were
 working through the BFS algorithm by hand to understand it, and then doing so
 again to debug my code.

Do you have any other remarks?

:Nope.
