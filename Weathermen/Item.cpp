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
	//setMaterial(material);
	setSymbol(symbol);
	setColor();
}