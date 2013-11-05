#include <vector>
#include <stdio.h>
#include <iostream>

#include "Item.h"

using namespace std;

void setName(string name);
void setDescription(string description);
void setSymbol(char symbol);

string getName();
string getDescription();
char getSymbol();

Item::Item(){
	setName("");
	setDescription("");
	setSymbol('%');
}

Item::Item(string name, string description, string material, char symbol){
	setName(name);
	setDescription(description);
	setMaterial(material);
	setSymbol(symbol);
	setColor();
}

void Item::setColor(){
	if (this->getMaterial().compare("GRASS") == 0){
		this->color[0] = 0;
		this->color[1] = 5;
		this->color[2] = 0;
		this->color[3] = 0;
	}else if (this->getMaterial().compare("ROCK") == 0){
		this->color[0] = 5;
		this->color[1] = 5;
		this->color[2] = 5;
		this->color[3] = 0;
	}

}