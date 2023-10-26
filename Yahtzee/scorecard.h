#pragma once
#include <vector>
#include <string>
#include <iostream>
#include<sstream>
#include<algorithm>
using namespace std;
class scorecard
{
public:

	scorecard(string scores[6]);
	~scorecard();
	void display();
	int getHighscore();
	int returnValues(int iter);

	
private:
	int gameID, totalScore;
	static int counter;
	int scoreArray[6];
	

};

