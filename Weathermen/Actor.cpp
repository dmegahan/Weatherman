#include <vector>
#include <stdio.h>
#include <iostream>

#include "Actor.h"

using namespace std;

void setName(string name);
void setDescription(string description);
void setSymbol(char symbol);

string getName();
string getDescription();
char getSymbol();

Actor::Actor(){
	setName("");
	setDescription("");
	setSymbol('%');
	setType("Actor");
	setColor();
}

Actor::Actor(int _x, int _y){
	x = _x;
	y = _y;

	setName("");
	setDescription("");
	setSymbol('%');
	setType("Actor");
	setColor();
}


Actor::Actor(int _x, int _y, string name, string description, string type, char symbol){
	x = _x;
	y = _y;

	setName(name);
	setDescription(description);
	setType(type);
	setSymbol(symbol);
	setColor();
}

void Actor::setColor(){
	if (this->getType().compare("PLAYER") == 0){
		this->color[0] = 0;
		this->color[1] = 0;
		this->color[2] = 5;
		this->color[3] = 0;
	}else{
		this->color[0] = 5;
		this->color[1] = 0;
		this->color[2] = 0;
		this->color[3] = 0;
	}
}