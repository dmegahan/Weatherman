#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <iostream>

using namespace std;

class Item{
	private:
		string item_name;
		string item_description;
		string item_material;
		char item_symbol;
		int color[4];

	public:
		Item();
		Item(string name, string description, string material, char symbol);

		void setName(string name){ item_name = name; }
		void setDescription(string description){ item_description = description; }
		void setMaterial(string material){ item_material = material; }
		void setSymbol(char symbol){ item_symbol = symbol; }
		void setColor();

		string getName(){ return item_name; }
		string getDescription(){ return item_description; }
		string getMaterial(){ return item_material; }
		char getSymbol(){ return item_symbol; }
		int *getColor(){ return color; }
};

#endif