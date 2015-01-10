#ifndef AI_H
#define AI_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>

#include "Actor.h"
#include "Map.h"

using namespace std;

class AI{
protected:
	Actor *actor;
	Map *map;
	//array of positions of tiles viewed by the NPC
	vector<std::array<int, 2>> viewed_tiles;
	
public:
	AI(Actor *actor, Map *map);
	bool isAdjacent(int orig_x, int orig_y, int dest_x, int dest_y);

	void nextAction();
	void behavior();

	void DoFOV(float x, float y);
	void FOV();
};

#endif