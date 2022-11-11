// Credit to https://github.com/codingcleverly/hangman_game
// Terminal command: g++ -std=c++11 main.cpp hangman_functions.cpp -o main.exe

#include <iostream>
#include <vector>
#include "hangman_functions.h"
#include <ctime>
using namespace std;

int main()
{
  intro();
  stage1("aluminum");
  stage2();
  hangmanGreet();
  
  vector<string> answers{"one", "two"};

  srand ( time(NULL) );

  string codeword = answers[rand() % answers.size()];
  string answer;

  for (int i = 0; i < codeword.length(); i++){
    answer.append("_");
  }

  int misses = 0;
  vector<char> incorrect;
  bool guess = false;
  char letter;

  while(answer!=codeword && misses < 7)
  {
    display_misses(misses);
    display_status(incorrect, answer);

    cout<<"\n\nPlease enter your guess: ";
    cin>>letter;

    letter = tolower(letter);

    for(int i = 0; i<codeword.length(); i++)
    {
      if(letter==codeword[i])
      {
        answer[i] = letter;
        guess = true;
      }
    }
    if(guess)
    {
      cout<<"\nCorrect!\n";
    }
    else
    {
      cout<<"\nIncorrect! Another portion of the person has been drawn.\n";
      incorrect.push_back(letter);
      misses++;
    }
    guess = false;
  }

  end_game(answer, codeword);

  endGame();

  return 0;
}