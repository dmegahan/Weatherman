#ifndef EQUIPTABLE_H
#define EQUIPTABLE_H

#include <stdio.h>
#include <iostream>

#include "Item.h"

#define DEFAULT_ITEM_SLOT "NA"

using namespace std;
/*
	Basic parent class for equiptable items
*/

class Equiptable : public Item{
private:
	string item_slot;

public:
	Equiptable();
	Equiptable(string name, string description, string material, char symbol, int weight, string item_slot);
};

#endif