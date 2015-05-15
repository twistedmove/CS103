/*Will Gauthier
email: wgauthie@usc.edu
This program runs a Monte Carlo simulation for the average number of turns it 
takes for one of three players to lose all his coins by flipping the same 
result as one other player.
Starting number of coins, number of games, and coin fairness are inputs.*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
 int initialCoins, numSimulations, playerCoins[3], tossReturn[3], turns = 0;
 double fairness, average;

 // Asks for and receives the user input values
 cout << "Enter the number of coins per player at the start of each game: ";
 cin >> initialCoins;
 cout << "Enter the probability a coin will be heads as a decimal between 0"
         << " and 1: ";
 cin >> fairness;
 cout << "Enter the total number of game simulations to be run: ";
 cin >> numSimulations;

 // Seeds the rand function
  srand(time(0));

 // Loop that runs all the games
 for (int g = 0; g < numSimulations; g++)
 {
  // Initializes the playercoins array with the given number of initial coins
  for (int i = 0; i < 3; i++)
  {
   playerCoins[i] = initialCoins;
  }
    
  // Loop that runs one full game
  while (playerCoins[0] != 0 && playerCoins[1] != 0 && playerCoins[2] != 0)
  {
   // Fills array of toss results
   for (int i = 0; i < 3; i++)
   {
    // Generates a random decimal number from 0 to 1 and provides a binary flip
    // result based on comparison with the fairness
    if (fairness < (double)rand()/RAND_MAX)
    {
     tossReturn[i] = 0;
    }
    else
    {
     tossReturn[i] = 1;
    }
   }

   if (tossReturn[0] == tossReturn[1])
   {
    // Player3 gets the coins
    if (tossReturn[1] != tossReturn[2])
    {
     playerCoins[0]--;
     playerCoins[1]--;
     playerCoins[2] += 2;
    }
    // A draw
   }
   // Player1 gets the coins
   else if (tossReturn[1] == tossReturn[2])
   {
    playerCoins[0] += 2;
    playerCoins[1]--;
    playerCoins[2]--;
   }
   // Player2 gets the coins
   else
   {
    playerCoins[0]--;
    playerCoins[1] += 2;
    playerCoins[2]--;
   }

   // Increases the turn counter
   turns++;
  }
 }

// Computes the average turns per game and outputs the result
average = (double)turns/(double)numSimulations;
cout << average << " average turns per game" << endl;

  return 0;
}
