#include <vector>
#include <stdio.h>
#include <iostream>

#include "Equiptable.h"

using namespace std;

Equiptable::Equiptable() : Item(){
	item_slot = DEFAULT_ITEM_SLOT;
}

Equiptable::Equiptable(string name, string description, string material, char symbol, int weight, string item_slot)
	: Item(name, description, material, symbol, weight){
	this->item_slot = item_slot;
}