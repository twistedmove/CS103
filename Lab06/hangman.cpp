// hangman.cpp
// Hangman game illustrates string library functions, 
// character arrays, arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype
int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char *wordBank[] = {"computer","president","trojan","program","coffee",
			  "library","football","popcorn","science","engineer"};

const int numWords = 10;

int main()
{
  srand(time(0));
  char guess;
  bool wordGuessed = false;
  int numTurns = 10;

  // Picks a random word from the wordBank
  const char* targetWord = wordBank[rand()%numWords];

  // A char array intialized with *'s for each character of the target word
  //  used to build up the answer
  char word[80];
  for (unsigned int i=0; i<strlen(targetWord); i++)
  {
    word[i] = '*';
  }
  // The last needed character in the array is set to null to make it a C-string
  word[strlen(targetWord)] = '\0';

  // An individual game continues until the word is guessed or 10 turns have elapsed
  while (numTurns > 0 && wordGuessed == false)
  {
    cout << "Current word: " << word << endl;
    cout << numTurns << " tries remain. . .Enter a letter to guess: ";
    cin >> guess;

    if(processGuess(word, targetWord, guess) == 0)
      numTurns--;

    if(strcmp(word, targetWord) == 0)
      wordGuessed = true;
  }

  // Print out end of game status
  if(wordGuessed == true)
    cout << "The word was \'" << targetWord << "\'. You win!" << endl;
  else
    cout << "Too many turns taken. You lose." << endl;

  return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to 
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char* word, const char* targetWord, char guess)
{
  int numGuessed = 0;

  for(unsigned int i=0; i<strlen(targetWord); i++)
  {
    if(targetWord[i] == guess)
    {
      word[i] = guess;
      numGuessed++;
    }
  }

  return numGuessed;
}

