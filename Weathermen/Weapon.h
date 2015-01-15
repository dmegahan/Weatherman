#ifndef WEAPON_H
#define WEAPON_H

#include <stdio.h>
#include <iostream>

#include "Equiptable.h"

using namespace std;

class Weapon : public Equiptable{
private:
	//sharp, blunt, ranged
	string weapon_type;
	int attack;
	float attack_speed;

public:
	Weapon();
	Weapon(string name, string description, string material, char symbol);
};

#endif