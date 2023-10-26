#pragma once
#include <iostream>
#include "dice.h"
#include <vector>
using namespace std;
class game
{
public:
	game();
	~game();
	void rollDice();
	int generateNumber();
	vector<int> runGame();
	bool lockDice(int i);
	void displayScores();
	
private:
	vector<dice*> dices;
	int round;
	vector<int> lockedScores = { NULL,NULL,NULL,NULL,NULL,NULL };
	vector<string> words = { "Aces","Twos","Threes","Fours","Fives","Sixes" };





};

