#ifndef MOVE_H
#define MOVE_H

#include <stdio.h>
#include <iostream>

#include "Tile.h"
#include "Action.h"

using namespace std;

class Move : public Action{
private:
	Tile *orig;
	Tile *dest;
	int dest_x;
	int dest_y;
public:
	Move(Tile *_orig, Tile *_dest, int _dest_x, int _dest_y);
	bool execute();
};

#endif