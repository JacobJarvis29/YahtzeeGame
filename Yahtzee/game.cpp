#include "game.h"
#include <stdlib.h>

game::game():round(0) {
}
game::~game() {

}
vector<int> game::runGame() {
	int scoreOption;
	for (int i = 0; i < 5; i++) {
		dices.push_back(new dice(0, false));
	}
	//Looping through so the player has multiple dice rolls, being allowed to lock
	//Or unlock each throw before choosing their score, looping for all six score options
	for (int i = 0; i < 6; i++) {

		while (round < 3) {
			rollDice();
		}
		cout << "\nWhich score would you like to lock in? ";
		for (int j = 0; j < lockedScores.size(); j++) {
			if (lockedScores[j] == NULL) {
				cout << j + 1 << ": " << words[j] <<"\n";

			}
			

		}
		int score = 0;
		cin >> scoreOption;
		//Loop through all of the die to check how many of the die are the value the player wants scored
		for (int j = 0; j < 5; j++) {
			if (dices[j]->isNumber(scoreOption)) {
				cout << "\nhi";
				score += 1;
			}
			cout << "\n" << score;
		}
		score *= scoreOption;
		lockedScores[scoreOption-1] = score;
		displayScores();
		round = 0;
		//Unlock the dice and start a new round
		for (int i = 0; i < 5; i++) {
			dices[i]->setLocked(false);
		}
	}
	for (int i = 0; i < dices.size(); i++) {
		delete dices[i];
	}
	return(lockedScores);
}
void game::displayScores() {
	for (int i = 0; i < 6; i++) {
		cout << "\n" << words[i] << ":" << lockedScores[i];
	}
}

void game::rollDice() {
	//Generates 5 die and asks the user if the want to lock them
	for (int i = 0; i < 5; i++) {
		if (!(dices[i]->isLocked())) {
			dices[i]->setValues(generateNumber());
		}
		dices[i]->display();
		
	}
	
	for (int i = 0; i < 5; i++) {

		dices[i]->setLocked(lockDice(i));
	}
	cout << "\n YOUR DICES AT THE END OF THIS ROLL ARE: ";
	for (int i = 0; i < 5; i++) {
		
		dices[i]->display();
	}

	cout << "\nNext Round";


		
	round = round + 1;
}

int game::generateNumber() {

	return (rand() % 6 + 1);
	
}

bool game::lockDice(int i) {
	string choice;
	cout << "\n Type L to lock dice: "<<i+1<<" ";
	cin >> choice;
	if (choice._Equal("L")) {
		cout << "Locking";
		return true;
	}
	else {
		return false;
	}
}
