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
	color.resize(4);

	setName(DEFAULT_ACTOR_NAME);
	setDescription(DEFAULT_ACTOR_DESCRIPTION);
	setSymbol(DEFAULT_ACTOR_SYMBOL);
	setType(DEFAULT_ACTOR_TYPE);
	setColor();

	inventory = new ItemContainer();
	state = DEFAULT_STATE;
	base_stats = DEFAULT_POINTS_FOR_STATS;
	view_radius = DEFAULT_VIEW_RADIUS;

	initializeStats();
	randomizeStats(base_stats);
}

Actor::Actor(int x, int y) : pos(x, y){
	color.resize(4);

	setName(DEFAULT_ACTOR_NAME);
	setDescription(DEFAULT_ACTOR_DESCRIPTION);
	setSymbol(DEFAULT_ACTOR_SYMBOL);
	setType(DEFAULT_ACTOR_TYPE);
	setColor();

	initializeStats();

	inventory = new ItemContainer();
	state = DEFAULT_STATE;
	base_stats = DEFAULT_POINTS_FOR_STATS;
	view_radius = DEFAULT_VIEW_RADIUS;

	initializeStats();
	randomizeStats(base_stats);
}


Actor::Actor(int x, int y, string name, string description, string type, char symbol) : pos(x, y){
	color.resize(4);

	setName(name);
	setDescription(description);
	setType(type);
	setSymbol(symbol);
	setColor();

	initializeStats();

	inventory = new ItemContainer();
	state = DEFAULT_STATE;
	base_stats = DEFAULT_POINTS_FOR_STATS;
	view_radius = DEFAULT_VIEW_RADIUS;

	initializeStats();
	randomizeStats(base_stats);
}

Actor::~Actor(){
	delete inventory;
}


void Actor::setColor(){
	if (this->getType().compare("PLAYER") == 0){
		//blue
		this->color[0] = 0;
		this->color[1] = 0;
		this->color[2] = 5;
		this->color[3] = 0;
	}else{
		//red
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
	STR, CON, INT, AGI, DEX, CHR, PER = DEFAULT_STARTING_STAT;

	current_hunger = DEFAULT_STARTING_HUNGER;
	current_thirst = DEFAULT_STARTING_THIRST;
	current_health = DEFAULT_STARTING_HEALTH;

	max_hunger = DEFAULT_MAX_HUNGER;
	max_thirst = DEFAULT_MAX_THIRST;
	max_health = DEFAULT_MAX_HEALTH;
}

void Actor::randomizeStats(int max_points){
	srand(time(NULL));

	int number_of_stats = NUMBER_OF_STATS;
	int spent_points = 0;

	vector<int*>stats = { &STR, &CON, &INT, &AGI, &DEX, &CHR, &PER };

	while (spent_points < max_points){
		int rand_stat = rand() % stats.size();
		//add a random number of points form 1 - 2 to a random stat
		int rand_points_given = rand() % 2 + 1;
		//printf("Stat: %d, Points to be given: %d\n", rand_stat, rand_points_given);
		if (stats.size() <= 0){
			return;
		}
		//number of points in 1 stat cannot exceed 10
		if ((*stats[rand_stat] + rand_points_given) <= 10){
			//add the random number of points to the stat
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
	}
}

void Actor::applyStats(){
	//apply effects of stats 
	//CON affects hunger, thirst, and health starting values;
	current_health = (CON * CURRENT_HEALTH_CON_MULTIPLIER) + current_health;
	current_hunger = (CON * CURRENT_HUNGER_CON_MULTIPLIER) + current_hunger;
	current_thirst = (CON * CURRENT_THIRST_CON_MULTIPLIER) + current_thirst;

	max_health = (CON * MAX_HEALTH_CON_MULTIPLIER) + max_health;
	max_hunger = (CON * MAX_HUNGER_CON_MULTIPLIER) + max_hunger;
	max_thirst = (CON * MAX_THIRST_CON_MULTIPLIER) + max_thirst;
}

/*
	Not the best name, but actionEffects will degrade stats like hunger and thirst ever time its called, as well as
	check the status of the character, including health, sickness, stamina 

	each action will have a certain amount of energy attached to it, and that will affect how fast you lose hunger/thirst, and affect
	other status effectsThis 
*/
void Actor::actionEffects(int energy_expended){
	current_hunger = current_hunger - energy_expended;
	current_hunger = current_thirst - energy_expended;
}


void Actor::applyDamage(int damage){
	//use CON to determine damage actually taken
	//this stat will reduce the damage by whatever % (currently 10 CON = 50% reduction)
	float damage_reduction_multiplier = (this->CON) * DEFAULT_DAMAGE_REDUCTION_MULTIPLIER;
	int true_damage = damage * (damage_reduction_multiplier / 100);

	this->current_health = this->current_health - true_damage;
	printf("Damage done: %d\n", true_damage);
	printf("Health after attack: %d\n", this->current_health);

	if (current_health <= 0){
		//die
	}
}