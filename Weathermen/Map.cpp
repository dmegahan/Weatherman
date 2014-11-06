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

void Map::newMove(int orig_x, int orig_y, int dest_x, int dest_y){
	Tile *orig = getTileAtPos(orig_x, orig_y);
	Tile *dest = getTileAtPos(dest_x, dest_y);

	if (orig != nullptr && dest != nullptr){
		q.push(new Move(orig, dest, dest_x, dest_y));
	}
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