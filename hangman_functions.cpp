#include <iostream>
#include <vector>
#include "hangman_functions.h"
using namespace std;
//define functions

void intro(){
  cout << "=====================\n";
  cout << "1998: The Great Ice Storm\n";
  cout << "=====================\n";
  cout << "Click enter to continue the story\n";
  cin.ignore();
  cout << "It's 1998, and you’re going home on winter break from Northeastern University. You’ve had a tough semester, finishing up your final requirements as an engineering major and you are very ready for your rest.";
  cout << "Waiting in Boston Logan Airport for your flight to JFK, you finish making your cup of coffee and start to head over to your sofa in the airport lounge.\n";
  cout << endl;
  cout << "You plan on making a phone call to your parents who you haven’t seen in months, updating them that you are almost home.";
  cout << "Suddenly, you hear surprised shouts as the lights go out in the lounge.\n";
  cout << "Bolting up in your chair, you realize that not only the lounge has gone dark, but the whole airport has as well. You look outside the window to see violent waves of snow falling down, enough to almost blur your vision.";
  cout << "In the corner of your eye you see sparks as the power lines disconnect from the power grids as they crumple down to the ground. It's the Great Ice Storm of 1998 and reluctantly, you realize that you are going to be stuck in the airport for a while.";
  cout << "Your task as the only engineer available is to fix this issue immediately\n";
  cout << endl;
  cout << "Click enter to continue the story\n";
  cin.ignore();
}

void stage1(string answer){
  cout << "=====================\n";
  cout << "Stage 1\n";
  cout << "=====================\n";
  cout << "The firefighters bring you outside to the crumpled powergrid. You see that one of the 3 power grids has fallen. They have found that the difference between the power grids is the material it is made out of. You are to find out which material it was\n";
  cout << endl;
  string userInput;
  while (true){
    cout << "Input your answer:\n";
    cin >> userInput;
    for_each(userInput.begin(), userInput.end(), [](char & c){
      c = tolower(c);
    });

    if (answer.compare(userInput) == 0){
      cout << "You got the correct material!\n";
      break;
    }else{
      cout << "You got the wrong material :( Try again.\n";
    }
  }
  cout << endl;
  cout << "=====================\n";
  cout << "Congradulation, you finished stage 1!\n";
}

void stage2(){
  cout << "=====================\n";
  cout << "Stage 2\n";
  cout << "=====================\n";
  cout << "Congratulations! The power grid is successfully fixed. Oh look! The lights are back on. You can hear the people celebrating and you have tens of people coming to thank you.\n";
  cout << "Click enter to continue the story\n";
  cin.ignore();
  cin.ignore();
  cout << "…Oh wait hold on! We’re getting complaints from neighbors. What else could they possibly want? Turns out, that while you were busy celebrating your initial win, you missed that the rest of the city is still missing power. There is still something wrong.\n";
}

void hangmanGreet(){
  cout << "=====================\n";
  cout << "Hangman: But you are guessing the letters\n";
  cout << "=====================\n";
  cout << "Instructions: Guess the correct inputs for the powerline.\n";
}

void display_misses(int misses){
  if(misses==0){
    cout<<"  +---+ \n";
    cout<<"  |   | \n";
    cout<<"      | \n";
    cout<<"      | \n";
    cout<<"      | \n";
    cout<<"      | \n";
    cout<<" ========= \n";
  }
  else if(misses==1){
    cout<<"  +---+ \n";
    cout<<"  |   | \n";
    cout<<"  O   | \n";
    cout<<"      | \n";
    cout<<"      | \n";
    cout<<"      | \n";
    cout<<" ========= \n";
  }else if(misses==2)
  {
    cout<<"  +---+ \n";
    cout<<"  |   | \n";
    cout<<"  O   | \n";
    cout<<"  |   | \n";
    cout<<"      | \n";
    cout<<"      | \n";
    cout<<" ========= \n";
  }else if(misses==3)
  {
    cout<<"  +---+ \n";
    cout<<"  |   | \n";
    cout<<"  O   | \n";
    cout<<" /|   | \n";
    cout<<"      | \n";
    cout<<"      | \n";
    cout<<" ========= \n";
  }else if(misses==4)
  {
    cout<<"  +---+ \n";
    cout<<"  |   | \n";
    cout<<"  O   | \n";
    cout<<" /|\\  | \n";
    cout<<"      | \n";
    cout<<"      | \n";
    cout<<" ========= \n";
  }else if(misses==5)
  {
    cout<<"  +---+ \n";
    cout<<"  |   | \n";
    cout<<"  O   | \n";
    cout<<" /|\\  | \n";
    cout<<" /    | \n";
    cout<<"      | \n";
    cout<<" ========= \n";
  }else if(misses==6)
  {
    cout<<"  +---+ \n";
    cout<<"  |   | \n";
    cout<<"  O   | \n";
    cout<<" /|\\  | \n";
    cout<<" / \\  | \n";
    cout<<"      | \n";
    cout<<" ========= \n";
  }
}


void display_status(vector<char> incorrect, string answer)
{
  cout<<"Incorrect Guesses: \n";

  for(int i = 0; i<incorrect.size(); i++){
    cout<<incorrect[i]<<" ";
  }

  cout<<"\nCodeword:\n";

  for(int i = 0; i<answer.length(); i++){
    cout<<answer[i]<<" ";
  }
}


void end_game(string answer, string codeword)
{
  if(answer==codeword){
    cout<<"Hooray! Now you just have to plugged in the cables\n";
    cout<<"Congratulations!\n";
  }else{
    cout<<"On no! The cables weren't plugged back in time\n";
    cout<<"Game over";
  }
}

void endGame()
{
  cout<<"\nCongratulations! The city is all lit up! Your help is greatly appreciated. You can now finally enjoy the rest of the vacation!";
  cout<<"\nGame end";
}