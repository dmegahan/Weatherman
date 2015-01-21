#include "Action.h"
#include "Attack.h"

using namespace std;

Attack::Attack(){
	cost = 1;
}

Attack::Attack(Actor *user, Actor *target){
	this->user = user;
	this->target = target;
}