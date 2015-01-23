#include "Action.h"
#include "Attack.h"

Attack::Attack(){
	cost = DEFAULT_COST;
}

Attack::Attack(Actor *user, Actor *target){
	this->user = user;
	this->target = target;
}