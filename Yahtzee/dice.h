#pragma once
#include <iostream>
using namespace std;
class dice
{
public:
	dice(int value,bool locked);
	~dice();
	bool isLocked();
	void display();
	void setValues(int valueIn);
	void setLocked(bool lockedIn);
	bool isNumber(int number);
	
private:
	bool locked;
	int diceID;
	static int counter;
	int value;
};

