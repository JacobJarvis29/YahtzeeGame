#pragma once
#include <string>
#include <iostream>
#include "game.h"
#include "scorecard.h"

using namespace std;

class player
{
public:
	player(string name, string password, int highscore);
	~player(); 
	bool checkData(string data,bool option);
	bool isSmaller(const player* player,bool option) const;
	void displayAll() const;
	void display() const;
	void displayScorecard(int i);
	bool endOfScores(int i);
	bool scorecardsNullMem();
	void readFile();
	void checkHighscore(int i);
	void averageScoreCalc();
	void startGame();
	void start(game& game);
	vector<string> writeFile();
	void writeIndivFile();
	void OOread();
	
private:
	bool read=false;
	int highscore,totalScore,playerID, amountOfScores;
	static int counter;
	float averageScore;
	string name,password;
	scorecard** scorecards = new scorecard*[1024];



};

