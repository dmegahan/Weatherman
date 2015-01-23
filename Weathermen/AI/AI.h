#ifndef AI_H
#define AI_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <memory>

#include "../Actors/Actor.h"
#include "../Game World/GameMap.h"

using namespace std;

class AI{
protected:
	Actor *actor;
	GameMap *g_map;
	//array of positions of tiles viewed by the NPC
	vector<Coordinate*> viewed_tiles;
	std::deque<Coordinate*> current_path;
	
	void deleteVectorOfPointers(vector<Coordinate*> vector);
public:
	AI(Actor *actor, GameMap *map);
	~AI();

	void nextAction();
	void behavior();

	void DoFOV(float x, float y);
	void FOV();

	std::deque<Coordinate*> aStarSearch(GameMap *map, int orig_x, int orig_y, int dest_x, int dest_y);
	std::deque<Coordinate*> make_path(map<Coordinate*, Coordinate*> came_from, Coordinate* current);
	int heuristic(int x1, int y1, int x2, int y2){ return abs(x1 - x2) + abs(y1 - y2); }
	Coordinate* lowestScore(vector<Coordinate*> open_set, map<Coordinate*, int> scores);
	
	bool compare_ints(int i, int j);
	bool isEqual(Coordinate* a1, Coordinate* a2);
	void remove_duplicate_from_vector(vector<array<int, 2>> vec, array<int, 2> item);
};

#endif