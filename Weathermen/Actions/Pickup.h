#ifndef PICKUP_H
#define PICKUP_H

#include <stdio.h>
#include <iostream>

#include "../Game World/Tile.h"
#include "../Actions/Action.h"

using namespace std;

class Pickup : public Action{
private:
	Tile *pos;
public:
	Pickup(Tile *pos);
	bool execute();
};

#endif