#include <stdio.h>
#include <iostream>

#include "Map.h"

Map::Map(){

}

Map::Map(int x, int y){
	size_x = x;
	size_y = y;

	map = new Tile*[size_x];
	for (int i = 0; i < size_x; i++){
		map[i] = new Tile[size_y];
	}
}

void Map::createMap(){
	for (int i = 0; i < size_x; i++){
		for (int j = 0; j < size_y; j++){
			if (i % 2 == 0 && j % 2 == 0){
				map[i][j] = Tile("WALL", "Iron", 2, "ROCK WALL", "ROCK WALL", false);
			}
			else{
				map[i][j] = Tile("GRASS", "Grass", 0, "GRASS", "GRASS", true);
			}
		}
	}
}

Tile* Map::getTileAtPos(int posx, int posy){
	if (posx < size_x && posy < size_y && posx >= 0 && posy >= 0){
		return &map[posy][posx];
	}
	return nullptr;
}

bool Map::newMove(int orig_x, int orig_y, int dest_x, int dest_y){
	Tile *orig = getTileAtPos(orig_x, orig_y);
	Tile *dest = getTileAtPos(dest_x, dest_y);

	if (orig != nullptr && dest != nullptr && dest->isEmpty()){
		q.push(new Move(orig, dest, dest_x, dest_y));
		return true;
	}
	return false;
}

bool Map::newPickUp(int orig_x, int orig_y){
	Tile *pos = getTileAtPos(orig_x, orig_y);

	if (pos != nullptr){
		q.push(new Pickup(pos));
		return true;
	}
	return false;
}

bool Map::newMeleeAttack(Actor* attacker, Actor* target){
	
	if (attacker != nullptr && target != nullptr){
		bool adj = isAdjacent(attacker->x, attacker->y, target->x, target->y);
		if (adj){
			q.push(new MeleeAttack(attacker, target));
			return true;
		}
	}
	return false;
}

void Map::executeQueue(){
	//gruesome
	bool result = false;
	while (!q.empty()){
		result = q.front()->execute();
		q.pop();
	}
}

void Map::resetVisibility(){
	for (int i = 0; i < size_x; i++){
		for (int j = 0; j < size_y; j++){
			map[i][j].VISIBLE = false;
		}
	}
}

bool Map::isAdjacent(int orig_x, int orig_y, int dest_x, int dest_y){
	if (abs(orig_x - dest_x) == 1){
		if (abs(orig_y - dest_y) == 0){
			return true;
		}
	}
	else if (abs(orig_x - dest_x) == 0){
		if (abs(orig_y - dest_y) == 1){
			return true;
		}
	}
	return false;
}