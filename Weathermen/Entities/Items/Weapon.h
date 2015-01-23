#ifndef WEAPON_H
#define WEAPON_H

#include <stdio.h>
#include <iostream>

#include "Equiptable.h"

#define DEFAULT_WEAPON_TYPE "NA"
#define DEFAULT_ATTACK_VALUE 1
#define DEFAULT_ATTACK_SPEED 0.1

using namespace std;

class Weapon : public Equiptable{
private:
	//sharp, blunt, ranged
	string weapon_type;
	int attack;
	float attack_speed;

public:
	Weapon();
	Weapon(string name, string description, string material, char symbol, int weight, 
			string item_slot, string weapon_type, int attack, float attack_speed);
};

#endif