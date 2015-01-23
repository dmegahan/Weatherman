#ifndef ARMOR_H
#define ARMOR_H

#include <stdio.h>
#include <iostream>

#include "Equiptable.h"

#define DEFAULT_ARMOR_TYPE "NA"
#define DEFAULT_ARMOR_VALUE 1

using namespace std;

class Armor : public Equiptable{
private:
	//amount of armor given
	int armor;
	//cloth, leather, mail?, plate?
	//cloth does not reduce damage on any attacks, but weighs the least
	//leather protects from most slashes, no protection from stabs
	string type;

public:
	Armor();
	Armor(string name, string description, string material, char symbol, 
					int weight, string item_slot, int armor, string type);
};

#endif