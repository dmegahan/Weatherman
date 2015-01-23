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

Item::Item() : Entity(){
	this->weight = DEFAULT_WEIGHT_VALUE;
}

Item::Item(string name, string description, string material, char symbol, int weight) : 
	Entity(name, description, material, symbol){

	this->weight = weight;
}