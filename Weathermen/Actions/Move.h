#ifndef MOVE_H
#define MOVE_H

#include "../Game World/Tile.h"
#include "../Actions/Action.h"

class Move : public Action{
private:
	Tile *orig;
	Tile *dest;
	int dest_x;
	int dest_y;
public:
	Move(Tile *orig, Tile *dest, Coordinate *coord);
	~Move();
	bool execute();
};

#endif