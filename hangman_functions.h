#include <iostream>
#include <vector>
using namespace std;

//declare functions
void intro();
void stage1(string answer);
void stage2();
void hangmanGreet();
void display_misses(int misses);
void display_status(vector<char> incorrect, string answer);
void end_game(string answer, string codeword);
void endGame();
