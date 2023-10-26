#include "dice.h"
int dice::counter = 1;
dice::dice(int value,bool locked) : value(value),locked(locked),diceID(counter++){


}

dice::~dice() {


}
bool dice::isLocked() {
	return(locked);
}

void dice::display() {
	if (locked) {
		cout << "\nDice " << diceID << " : " << value << " - LOCKED";
	}
	else {
		cout << "\nDice " << diceID << " : " << value << " - UNLOCKED";
	}
}
void dice::setValues(int valueIn) {
	value = valueIn;
}
void dice::setLocked(bool lockedIn) {
	locked = lockedIn;
}

bool dice::isNumber(int number) {
	
	return(number == value);
}