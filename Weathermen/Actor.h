#ifndef ACTOR_H
#define ACTOR_H

#include <stdio.h>
#include <iostream>
#include "Action.h"
#include "ItemContainer.h"

using namespace std;

class Actor{
	private:
		string actor_name;
		string actor_description;
		string actor_type;
		char actor_symbol;
		vector<float> color;

		int base_stats;
		ItemContainer *inventory;
	public:
		int x;
		int y;

		int STR;
		int CON;
		int INT;
		int AGI;
		int DEX;
		int CHR; 
		int PER;

		int current_hunger;
		int current_thirst;
		int current_health;

		int max_hunger;
		int max_thirst;
		int max_health;

		int view_radius;
		string state;

		Actor();
		Actor(int _x, int _y);
		Actor(int _x, int _y, string name, string description, string type, char symbol);

		void setName(string name){ actor_name = name; }
		void setDescription(string description){ actor_description = description; }
		void setType(string type){ actor_type = type; }
		void setSymbol(char symbol){ actor_symbol = symbol; }
		
		void initializeStats();
		void randomizeStats(int max_points);
		void applyStats();

		void actionEffects(int energy_expended = 0);
		void applyDamage(int damage);
		
		void setColor();
		vector<float> getColor(){ return color; }

		string getName(){ return actor_name; }
		string getDescription(){ return actor_description; }
		string getType(){ return actor_type; }
		char getSymbol(){ return actor_symbol; }

		ItemContainer* getInventory(){ return inventory; }
};

#endif