#include <vector>
#include <stdio.h>
#include <iostream>

#include "Weapon.h"

using namespace std;

Weapon::Weapon() : Equiptable(){
	this->weapon_type = "NA";
	this->attack = 1;
	this->attack_speed = 0.1;
}

Weapon::Weapon(string name, string description, string material, char symbol, int weight,
	string item_slot, string weapon_type, int attack, float attack_speed)
	: Equiptable(name, description, material, symbol, weight, item_slot){
	this->weapon_type = weapon_type;
	this->attack = attack;
	this->attack_speed = attack_speed;
}