#pragma once
#include <string>
#include <iostream>
#include <list>
using namespace std;
class menu
{
public:
	menu(list<string> options);
	~menu();
	void displayOptions();


private:
	list<string> options;

};

