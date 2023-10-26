#include "player.h"
#include <iostream>
#include<fstream>
using namespace std;

int player::counter = 0; 

player::player(string name, string password,int highscore) : playerID(counter++), name(name), password(password),highscore(highscore),totalScore(0),averageScore(0) {

}
player::~player() {
	delete scorecards;
	



}

void player::displayAll() const {
	//used in the player menu to show their stats
	cout << "Name: " << name
	<< "\nHighscore: " << highscore
	<< "\nAccumulated Score: " << totalScore
	<< "\nNo of Games: " << amountOfScores
	<< "\nAverage Score: " << averageScore<<"\n";

}

void player::display() const {
	//Used to loop through and display each player
	cout <<playerID <<" "<< name << "    " << highscore << "\n";

}

bool player::checkData(string data,bool option) {
	//Verify password and username, taking bool to decide which 
	if (option) {
		return(data._Equal(name));
		
	}
	else
	{
		return(data._Equal(password));
		
	}
}


bool player::isSmaller(const player* player, bool option) const
{	

	//Both sort functions, for alphabetically and highscore, using a bool again to determine
	if (option) {
		return (name < (*(player)).name);
	}
	else {
		return (highscore > (*(player)).highscore);
	}
}

void player::readFile() {
	//Reads in the indivudal player's score history
	ifstream file(name+".csv");
	string line;
	int index = 0;
	amountOfScores = 0;
	string data[6];
	while (getline(file, line))
	{
		istringstream iss(line);
		
		string result;
		while (getline(iss, result, ','))
		{
			
			data[index] = result;
			index++;
		}
		
		scorecards[amountOfScores] = new scorecard(data);
		amountOfScores++;
		index = 0;
	}
	//Sets a boolean value so that the system can check and know if we have read their file yet
	read = true;

}



bool player::scorecardsNullMem() {
	return(read);
}

void player::displayScorecard(int i) {
	scorecards[i]->display();
}
bool player::endOfScores(int i) {
	return(i >= amountOfScores);
}
void player::checkHighscore(int i) {
	int tempScore = scorecards[i]->getHighscore();
	if (tempScore > highscore) {
		highscore = tempScore;
	}
}
void player::averageScoreCalc() {
	float temp = 0;
	for (int i = 0; i < amountOfScores; i++) {
		temp += float(scorecards[i]->getHighscore());
	}
	if (temp == 0) {
		averageScore = 0;
	}else{
		averageScore = temp / amountOfScores;
	}
	
	totalScore = temp;
}

void player::startGame() {
	//Creating a new game instance
	game game1{};
	start(game1);
	

}
void player::start(game& game)
{
	vector<int> scores;
	string data[6];
	scores = game.runGame();
	for (int i=0; i < scores.size(); i++) {
		data[i] = to_string(scores[i]);
	}
	scorecards[amountOfScores] = new scorecard(data);
	checkHighscore(amountOfScores);
	amountOfScores++;
	
}
vector<string> player::writeFile() {
	vector<string> values = { name, password, to_string(highscore) };
	return values;
}
void player::writeIndivFile()
{
	//Looping through all of the scorecards and writing them back
	ofstream myfile;
	myfile.open(name + ".csv");
	string data [6];
	for (int i = 0; i < amountOfScores; i++) {
		for (int j = 0; j < 6; j++) {
			data[j] = (to_string(scorecards[i]->returnValues(j)));
			
		}
		myfile << data[0] << "," << data[1] << "," << data[2] << ","
			   << data[3] << "," << data[4] << "," << data[5] << "\n";
		delete scorecards[i];
		scorecards[i] = nullptr;

	}

	myfile.close();

}
