#include "Action.h"
#include "Attack.h"
#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(Actor *user, Actor *target) : Attack(){
	this->user = user;
	this->target = target;
}

bool MeleeAttack::execute(){
	//calculate damage by using strength as a parameter
	int damage = user->STR;

	//caluclate hit chance (perception + dexterity)
	int hit_rating_DEX = user->DEX * HIT_RATING_DEX_MULTIPLIER;
	int hit_rating_PER = user->PER * HIT_RATING_PER_MULTIPLIER;
	//the * 10 makes the hit_chance a "percentage" in the range of 0-100+ to hit
	float hit_chance = (hit_rating_DEX + hit_rating_PER) / HIT_RATING_DIVIDER * 10;
	printf("DEX: %d\n", user->DEX);
	printf("PER: %d\n", user->PER);
	printf("hit_rating_DEX: %d\n", hit_rating_DEX);
	printf("hit_rating_PER: %d\n", hit_rating_PER);
	printf("hit_chance: %f\n", hit_chance);

	//calculate targets dodge chance (agility + perception)
	int dodge_rating_AGI = target->AGI * DODGE_RATING_AGI_MULTIPLIER;
	int dodge_rating_PER = target->PER * DODGE_RATING_PER_MULTIPLIER;
	//the * 10 makes the hit_chance a "percentage" in the range of 0-100+ to dodge
	float dodge_chance = (dodge_rating_AGI + dodge_rating_PER) / DODGE_RATING_DIVIDER * 10;
	printf("AGI: %d\n", target->AGI);
	printf("PER: %d\n", target->PER);
	printf("dodge_chance: %f\n", dodge_chance);

	//roll for hit and dodge
	srand(time(NULL));
	//these rolls will be 0-100.0, if the roll is less than the chance to hit/dodge, it is successful
	float hit_roll = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100.0));
	printf("hit_roll: %f\n", hit_roll);
	if (hit_roll < hit_chance){
		//hit! check for dodge
		float dodge_roll = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100.0));
		if (dodge_roll < dodge_chance){
			//dodge!
			printf("Dodge. nothing happens.\n");
		}
		else{
			printf("hit went through\n");
			target->applyDamage(damage);
		}
	}
	else{
		printf("miss\n");
	}
	return true;
}