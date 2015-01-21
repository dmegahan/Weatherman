#include <vector>
#include <stdio.h>
#include <iostream>

#include "Entity.h"

using namespace std;

void setName(string name);
void setDescription(string description);
void setSymbol(char symbol);

string getName();
string getDescription();
char getSymbol();

Entity::Entity(){
	setName("");
	setDescription("");
	setSymbol('%');
}

Entity::Entity(string name, string description, string material, char symbol){
	setName(name);
	setDescription(description);
	//setMaterial(material);
	setSymbol(symbol);
	setColor();
}

void Entity::setColor(){
	this->color[0] = getMaterial().getColor()[0];
	this->color[1] = getMaterial().getColor()[1];
	this->color[2] = getMaterial().getColor()[2];
	this->color[3] = getMaterial().getColor()[3];
}