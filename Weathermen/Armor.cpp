#include <vector>
#include <stdio.h>
#include <iostream>

#include "Armor.h"

using namespace std;

Armor::Armor() : Equiptable(){
	armor = 0;
	type = "NA";
}

Armor::Armor(string name, string description, string material, char symbol, 
	int weight, string item_slot, int armor, string type)
	: Equiptable(name, description, material, symbol, weight, item_slot){
	this->armor = armor;
	this->type = type;
}
