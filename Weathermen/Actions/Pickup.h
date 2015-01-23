#ifndef PICKUP_H
#define PICKUP_H

#include "../Game World/Tile.h"
#include "../Actions/Action.h"

class Pickup : public Action{
private:
	Tile *pos;
public:
	Pickup(Tile *pos);
	~Pickup();
	bool execute();
};

#endif