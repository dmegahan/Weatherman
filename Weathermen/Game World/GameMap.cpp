#include <stdio.h>
#include <iostream>

#include "GameMap.h"

GameMap::GameMap(){

}

GameMap::GameMap(int x, int y){
	size_x = x;
	size_y = y;

	map = new Tile*[size_x];
	for (int i = 0; i < size_x; i++){
		map[i] = new Tile[size_y];
	}
}

void GameMap::createMap(){
	for (int i = 0; i < size_x; i++){
		for (int j = 0; j < size_y; j++){
			if (i == 2 && j == 2){
				map[i][j] = Tile("WALL", "Iron", 2, "ROCK WALL", "ROCK WALL", false);
			}
			else{
				map[i][j] = Tile("GRASS", "Grass", 0, "GRASS", "GRASS", true);
			}
		}
	}
}

Tile* GameMap::getTileAtPos(int posx, int posy){
	if (posx < size_x && posy < size_y && posx >= 0 && posy >= 0){
		return &map[posy][posx];
	}
	return nullptr;
}

bool GameMap::newMove(int orig_x, int orig_y, int dest_x, int dest_y){
	Tile *orig = getTileAtPos(orig_x, orig_y);
	Tile *dest = getTileAtPos(dest_x, dest_y);

	if (orig != nullptr && dest != nullptr){
		q.push(new Move(orig, dest, dest_x, dest_y));
		return true;
	}
	return false;
}

bool GameMap::newPickUp(int orig_x, int orig_y){
	Tile *pos = getTileAtPos(orig_x, orig_y);

	if (pos != nullptr){
		q.push(new Pickup(pos));
		return true;
	}
	return false;
}

bool GameMap::newMeleeAttack(Actor* attacker, Actor* target){
	
	if (attacker != nullptr && target != nullptr){
		bool adj = isAdjacent(attacker->x, attacker->y, target->x, target->y);
		if (adj){
			q.push(new MeleeAttack(attacker, target));
			return true;
		}
	}
	return false;
}

void GameMap::executeQueue(){
	//gruesome
	bool result = false;
	while (!q.empty()){
		result = q.front()->execute();
		q.pop();
	}
}

void GameMap::resetVisibility(){
	for (int i = 0; i < size_x; i++){
		for (int j = 0; j < size_y; j++){
			map[i][j].VISIBLE = false;
		}
	}
}

bool GameMap::isAdjacent(int orig_x, int orig_y, int dest_x, int dest_y){
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

vector<array<int, 2>> GameMap::getNeighbors(int pos_x, int pos_y){
	vector<array<int, 2>> neighbors;
	for (int i = 0; i < 3; i++){ //8 potential neighbors depending on location plus origin
		int new_x, new_y = -1;
		//assuming a point of 2,2 - there are 8 possible neighbors
		//1,1 - 1,2 - 1,3 - 2,1 - 2,3 - 3,1 - 3,2 - 3,3
		if (i % 3 == 0){
			//this conditional decrements pos
			if (pos_x - 1 >= 0){
				new_x = pos_x - 1;
				new_y = pos_y;

				neighbors.push_back({ { new_x, new_y } });
			}
		}
		else if (i % 3 == 1){
			new_x = pos_x;

			if (pos_y - 1 >= 0){
				new_y = pos_y - 1;
				neighbors.push_back({ { new_x, new_y } });
			}

			if (pos_y + 1 < size_y){
				new_y = pos_y + 1;
				neighbors.push_back({ { new_x, new_y } });
			}
		}
		else if (i % 3 == 2){
			if (pos_x + 1 < size_x){
				new_x = pos_x + 1;
				new_y = pos_y;
				neighbors.push_back({ { new_x, new_y } });
			}
		}
	}
	return neighbors;
}