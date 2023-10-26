#include "scorecard.h"
int scorecard::counter = 1;

scorecard::scorecard(string scores[6]) {
	//intialises scores and calculates the total score
	int array[] = { 0,0,0,0,0,0 };
	int tempNumb=0;
	gameID = counter++;
	totalScore = 0;
	for (int i = 0; i < 6; i++) {
		tempNumb = stoi(scores[i]);
		scoreArray[i] = tempNumb;
		totalScore += tempNumb;
	}
	

}
int scorecard::returnValues(int iter) {
	return scoreArray[iter];
}
scorecard::~scorecard() {

}
int scorecard::getHighscore() {
	return(totalScore);
}


void scorecard::display() {
	cout << "\nGame ID: " <<  gameID<< "\n"
		 << "Aces: " << scoreArray[0] << "\n"
		 << "Twos: " << scoreArray[1] << "\n"
		 << "Threes: " << scoreArray[2] << "\n"
		 << "Fours: " << scoreArray[3] << "\n"
		 << "Fives: " << scoreArray[4] << "\n"
		 << "Sixes: " << scoreArray[5] << "\n"
		 << "Total Score: " << totalScore << "\n";

}

