#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <iostream>
#include "Material.h"

#define DEFAULT_ITEM_NAME "default"
#define DEFAULT_ITEM_DESCRIPTION "description"
#define DEFAULT_ITEM_SYMBOL '%'

using namespace std;

class Entity{
private:
	string item_name;
	string item_description;
	Material item_material;
	char item_symbol;
	float color[4];

public:
	Entity();
	Entity(string name, string description, string material, char symbol);

	void setName(string name){ item_name = name; }
	void setDescription(string description){ item_description = description; }
	void setMaterial(Material material){ item_material = material; }
	void setSymbol(char symbol){ item_symbol = symbol; }
	void setColor();

	string getName(){ return item_name; }
	string getDescription(){ return item_description; }
	Material getMaterial(){ return item_material; }
	char getSymbol(){ return item_symbol; }
	float *getColor(){ return color; }
};

#endif