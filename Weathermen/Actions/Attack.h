#ifndef ATTACK_H
#define ATTACK_H

#include <time.h>
#include "Action.h"
#include "../Actors/Actor.h"

class Attack : public Action{
protected:
	Actor *user;
	Actor *target;

public:
	Attack();
	Attack(Actor *user, Actor *target);
	~Attack();

	virtual bool execute(){ return true; }
};

#endif