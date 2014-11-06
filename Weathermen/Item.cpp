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
	this->color[0] = getMaterial().getColor()[0];
	this->color[1] = getMaterial().getColor()[1];
	this->color[2] = getMaterial().getColor()[2];
	this->color[3] = getMaterial().getColor()[3];
}