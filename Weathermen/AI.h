#ifndef AI_H
#define AI_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>
#include <map>

#include "Actor.h"
#include "GameMap.h"

using namespace std;

class AI{
protected:
	Actor *actor;
	GameMap *g_map;
	//array of positions of tiles viewed by the NPC
	vector<std::array<int, 2>> viewed_tiles;
	
public:
	AI(Actor *actor, GameMap *map);

	void nextAction();
	void behavior();

	void DoFOV(float x, float y);
	void FOV();

	vector<array<int, 2>> aStarSearch(GameMap *map, int orig_x, int orig_y, int dest_x, int dest_y);
	vector<array<int, 2>> make_path(map<array<int, 2>, array<int, 2>> came_from, array<int, 2> current);
	int heuristic(int x1, int y1, int x2, int y2);
	array<int, 2> lowestScore(vector<array<int, 2>> open_set, map<array<int, 2>, int> scores);
	bool compare_ints(int i, int j);
	bool isEqual(array<int, 2> a1, array<int, 2> a2);
};

#endif