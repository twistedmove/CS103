// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

// Prototype
void permute(char items[], int len);

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    cout << "Usage: program_name, word_bank_file.txt" << endl;

    return 0;
  }

  ifstream wordBankFile (argv[1]); 
  if (wordBankFile.fail())
  {
    cout << "Failed to open file: " << argv[1] << endl;
  
    return 0;
  }

  int numWords;
  wordBankFile >> numWords;
  if (wordBankFile.fail())
  {
    cout << "Failed to find integer at the start of the file." << endl;

    return 0;
  }

  
  char** wordBank = new char*[numWords];

  char buffer[41];
  for (int i = 0; i < numWords; i++)
  {
    wordBankFile >> buffer;
    wordBank[i] = new char[strlen(buffer)+1];
    strcpy(wordBank[i], buffer);
  }

  wordBankFile.close();  

  srand(time(0));
  char guess[80];

  bool wordGuessed = false;
  int numTurns = 10;

  // Pick a random word from the wordBank
  int target = rand() % numWords;
  int targetLen = strlen(wordBank[target]);

  // More initialization code
  char* word = new char[targetLen+1];
  strcpy(word, wordBank[target]);
  permute(word, targetLen);
  
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while ( !wordGuessed && numTurns > 0 ){
    cout << "\nCurrent word:  " << word << endl;
    cin >> guess;
    wordGuessed = (strncmp(guess, wordBank[target], targetLen+1) == 0);
    numTurns--;
  }
  if(wordGuessed){
    cout << "You win!" << endl;
  }
  else {
    cout << "Too many turns...You lose!" << endl;
  }

  delete [] word;
  for (int i = 0; i < numWords; i++)
  {
    delete [] wordBank[i];
  }
  delete [] wordBank;

  return 0;
}

// Scramble the letters
void permute(char items[], int len)
{
  for(int i=len-1; i > 0; --i){
    int r =  rand() % i;
    int temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}

