#ifndef ARMOR_H
#define ARMOR_H

#include <stdio.h>
#include <iostream>

#include "Equiptable.h"

using namespace std;

class Armor : public Equiptable{
private:
	int armor;


public:
	Armor();
	Armor(string name, string description, string material, char symbol);
};

#endif