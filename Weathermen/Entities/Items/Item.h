#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <iostream>

#include "../Entity.h"

#define DEFAULT_WEIGHT_VALUE 1

using namespace std;

/*
	The basic item. This could be food, a potion, a piece of wood, some herbs, or bullets.
*/
class Item : public Entity{
	private:
		//maybe make this an object of its own or a enum

	public:
		int weight;

		Item();
		Item(string name, string description, string material, char symbol, int weight);

		//use will apply the effect
		void use();
};

#endif