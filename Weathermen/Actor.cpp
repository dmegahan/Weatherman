#include <vector>
#include <stdio.h>
#include <iostream>
#include <time.h>

#include "Actor.h"

using namespace std;

void setName(string name);
void setDescription(string description);
void setSymbol(char symbol);

string getName();
string getDescription();
char getSymbol();

Actor::Actor(){
	setName("");
	setDescription("");
	setSymbol('%');
	setType("Actor");
	setColor();

	base_stats = 28;

	view_radius = 5;

	initializeStats();

	inventory = new ItemContainer();
}

Actor::Actor(int _x, int _y){
	x = _x;
	y = _y;

	view_radius = 5;

	setName("");
	setDescription("");
	setSymbol('%');
	setType("Actor");
	setColor();

	//70 possible points, halve that - 7 gets 28. enough for 5s across the board
	base_stats = 28;

	initializeStats();

	inventory = new ItemContainer();
}


Actor::Actor(int _x, int _y, string name, string description, string type, char symbol){
	x = _x;
	y = _y;

	view_radius = 5;

	setName(name);
	setDescription(description);
	setType(type);
	setSymbol(symbol);
	setColor();

	base_stats = 28;

	initializeStats();

	randomizeStats(base_stats);

	inventory = new ItemContainer();
}


void Actor::setColor(){
	if (this->getType().compare("PLAYER") == 0){
		this->color[0] = 0;
		this->color[1] = 0;
		this->color[2] = 5;
		this->color[3] = 0;
	}else{
		this->color[0] = 5;
		this->color[1] = 0;
		this->color[2] = 0;
		this->color[3] = 0;
	}
}

/*
	Initialize stats to 1, the minimum stat value possible
*/
void Actor::initializeStats(){
	STR = 1;
	CON = 1;
	INT = 1;
	AGI = 1;
	DEX = 1;
	CHR = 1;
	PER = 1;

	hunger = 50;
	thirst = 50;
}

void Actor::randomizeStats(int max_points){
	srand(time(NULL));

	int number_of_stats = 7;
	int spent_points = 0;

	vector<int*>stats;
	stats.push_back(&STR);
	stats.push_back(&CON);
	stats.push_back(&INT);
	stats.push_back(&AGI);
	stats.push_back(&DEX);
	stats.push_back(&CHR);
	stats.push_back(&PER);

	while (spent_points != max_points){
		int rand_stat = rand() % stats.size();
		int rand_points_given = rand() % 2 + 1;
		//printf("Stat: %d, Points to be given: %d\n", rand_stat, rand_points_given);
		if ((*stats[rand_stat] + rand_points_given) <= 10){
			*stats[rand_stat] = *stats[rand_stat] + rand_points_given;
			spent_points = spent_points + rand_points_given;
		}
		else{
			//greater than 10, so add points up to 10, add amount of used points to spent_points, and remove stat from vector
			*stats[rand_stat] = *stats[rand_stat] + rand_points_given;
			int remainder = *stats[rand_stat] - 10;
			*stats[rand_stat] = *stats[rand_stat] - remainder;
			spent_points = spent_points + rand_points_given - remainder;
			stats.erase(stats.begin()+rand_stat);
		}
		if (stats.size() <= 0){
			return;
		}
	}
}

/*
	Not the best name, but actionEffects will degrade stats like hunger and thirst ever time its called, as well as
	check the status of the character, including health, sickness, stamina 

	each action will have a certain amount of energy attached to it, and that will affect how fast you lose hunger/thirst, and affect
	other status effectsThis 
*/
void Actor::actionEffects(int energy_expended){
	hunger = hunger - 1;
	thirst = thirst - 1;
}

ItemContainer* Actor::getInventory(){
	return inventory;
}