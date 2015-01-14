#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <Windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <queue>

#include "Action.h"
#include "Move.h"
#include "Pickup.h"
#include "MeleeAttack.h"
#include "Tile.h"

using namespace std;

class Map{
private:
	int size_x;
	int size_y;

	Tile **map;
	std::queue<Action*> q;
public:

	Map();
	Map(int x, int y);

	int getSizeX(){
		return size_x;
	}
	
	int getSizeY(){
		return size_y;
	}

	void createMap();
	void drawTiles();
	bool isAdjacent(int orig_x, int orig_y, int dest_x, int dest_y);

	Tile* getTileAtPos(int posx, int posy);

	bool newMove(int orig_x, int orig_y, int dest_x, int dest_y);
	bool newPickUp(int orig_x, int orig_y);
	bool newMeleeAttack(Actor *attacker, Actor* target);
	void executeQueue();

	void resetVisibility();
};

#endif