#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <Windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <queue>
#include <array>

#include "../Actions/Action.h"
#include "../Actions/Move.h"
#include "../Actions/Pickup.h"
#include "../Actions/MeleeAttack.h"
#include "Tile.h"

using namespace std;

class GameMap{
private:
	int size_x;
	int size_y;

	Tile **map;
	std::queue<Action*> q;
public:

	GameMap();
	GameMap(int x, int y);

	int getSizeX(){
		return size_x;
	}
	
	int getSizeY(){
		return size_y;
	}

	void createMap();
	void drawTiles();
	bool isAdjacent(int orig_x, int orig_y, int dest_x, int dest_y);
	vector<array<int, 2>> getNeighbors(int pos_x, int pos_y);

	Tile* getTileAtPos(int posx, int posy);

	bool newMove(int orig_x, int orig_y, int dest_x, int dest_y);
	bool newPickUp(int orig_x, int orig_y);
	bool newMeleeAttack(Actor *attacker, Actor* target);
	void executeQueue();

	void resetVisibility();
};

#endif