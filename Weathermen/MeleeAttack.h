#ifndef MELEEATTACK_H
#define MELEEATTACK_H

#include <stdio.h>
#include <iostream>
#include <time.h>

#include "Attack.h"

using namespace std;

class MeleeAttack : public Attack{
protected:
	Actor *user;
	Actor *target;

public:
	MeleeAttack(Actor *user, Actor *target);
	virtual bool execute();
};

#endif