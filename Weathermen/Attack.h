#ifndef ATTACK_H
#define ATTACK_H

#include <stdio.h>
#include <iostream>
#include <time.h>

#include "Action.h"
#include "Actor.h"

using namespace std;

class Attack : public Action{
protected:
	Actor *user;
	Actor *target;

public:
	Attack();
	Attack(Actor *user, Actor *target);
	virtual bool execute(){ return true; }
};

#endif