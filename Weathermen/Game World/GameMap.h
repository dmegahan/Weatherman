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

typedef std::array<int, 2> Coord;

class GameMap{
private:
	int size_x;
	int size_y;

	Tile **map;
	std::queue<Action*> q;
public:

	GameMap();
	GameMap(int x, int y);
	~GameMap();

	int getSizeX(){
		return size_x;
	}
	
	int getSizeY(){
		return size_y;
	}

	void createMap();
	void drawTiles();
	bool isAdjacent(Coordinate* orig, Coordinate* dest);
	vector<Coord> getNeighbors(int pos_x, int pos_y);

	Tile* getTileAtPos(Coordinate *pos);
	Tile* getTileAtPos(int x, int y);

	bool validateCoordinate(Coordinate* coord);

	bool newMove(Coordinate *orig, Coordinate *dest);
	bool newPickUp(Coordinate *pos);
	bool newMeleeAttack(Actor *attacker, Actor* target);
	void executeQueue();

	void resetVisibility();
};

#endif