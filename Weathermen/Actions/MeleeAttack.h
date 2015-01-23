#ifndef MELEEATTACK_H
#define MELEEATTACK_H

#include <time.h>
#include "Attack.h"

/*
	These multipliers affect the outcome of execute() by affecting the chance of a dodge/hit based
	on their labeled attribute (example: hit_rating_DEX = user->DEX * HIT_RATING_DEX_MULTIPLIER)
	Each mutliplier assigns a point value per attribute point (DEX gets 10 "points" per point of DEX)
*/
#define HIT_RATING_DEX_MULTIPLIER 10
#define HIT_RATING_PER_MULTIPLIER 5
#define DODGE_RATING_AGI_MULTIPLIER 10
#define DODGE_RATING_PER_MULTIPLIER 5
//The divider is used by dividing the total points gained from stats by itself, to determine a chance of hit/dodge
#define HIT_RATING_DIVIDER 15
#define DODGE_RATING_DIVIDER 30

class MeleeAttack : public Attack{
protected:
	Actor *user;
	Actor *target;
public:
	MeleeAttack(Actor *user, Actor *target);
	~MeleeAttack();
	virtual bool execute();
};

#endif