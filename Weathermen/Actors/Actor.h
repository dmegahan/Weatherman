#ifndef ACTOR_H
#define ACTOR_H

#include <stdio.h>
#include <iostream>
#include "../Actions/Action.h"
#include "../ItemContainer.h"
#include "../Game World/Coordinate.h"

//number of total points actors have to split into the 7 stats
//70 possible points, halve that - 7 gets 28. enough for 5s across the board
#define DEFAULT_POINTS_FOR_STATS 28
//how many points in stats you start with in initializeStats()
#define DEFAULT_STARTING_STAT 1
#define NUMBER_OF_STATS 7

#define DEFAULT_ACTOR_NAME ""
#define DEFAULT_ACTOR_DESCRIPTION ""
#define DEFAULT_ACTOR_SYMBOL '%'
#define DEFAULT_ACTOR_TYPE "Actor"
#define DEFAULT_VIEW_RADIUS 5
#define DEFAULT_STATE "normal"

#define DEFAULT_STARTING_HUNGER 75
#define DEFAULT_STARTING_THIRST 75
#define DEFAULT_STARTING_HEALTH 75
#define DEFAULT_MAX_HUNGER 100
#define DEFAULT_MAX_THIRST 100
#define DEFAULT_MAX_HEALTH 100

//multipliers for CON that give bonuses to starting health/hunger/thirst and max health/hunger/thirst
#define CURRENT_HEALTH_CON_MULTIPLIER 10
#define CURRENT_HUNGER_CON_MULTIPLIER 2
#define CURRENT_THIRST_CON_MULTIPLIER 2
#define MAX_HEALTH_CON_MULTIPLIER 10
#define MAX_HUNGER_CON_MULTIPLIER 5
#define MAX_THIRST_CON_MULTIPLIER 5

#define DEFAULT_ENERGY_EXPENDED 1
#define DEFAULT_DAMAGE_REDUCTION_MULTIPLIER 5

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
		Coordinate pos;

		int STR, CON, INT, AGI, DEX, CHR, PER;

		int current_hunger, current_thirst, current_health;

		int max_hunger, max_thirst, max_health;

		int view_radius;
		string state;

		Actor();
		Actor(int _x, int _y);
		Actor(int _x, int _y, string name, string description, string type, char symbol);
		~Actor();

		void setName(string name){ actor_name = name; }
		void setDescription(string description){ actor_description = description; }
		void setType(string type){ actor_type = type; }
		void setSymbol(char symbol){ actor_symbol = symbol; }
		
		void initializeStats();
		void randomizeStats(int max_points);
		void applyStats();

		void actionEffects(int energy_expended = DEFAULT_ENERGY_EXPENDED);
		void applyDamage(int damage);
		
		void setColor();
		vector<float> getColor(){ return color; }

		string getName(){ return actor_name; }
		string getDescription(){ return actor_description; }
		string getType(){ return actor_type; }
		char getSymbol(){ return actor_symbol; }
		Coordinate* getPos(){ return &pos; }

		ItemContainer* getInventory(){ return inventory; }
};

#endif