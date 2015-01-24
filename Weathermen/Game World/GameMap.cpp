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

GameMap::~GameMap(){
	for (int i = 0; i < q.size(); i++){
		Action* action = q.front();
		q.pop();
		delete action;
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

bool GameMap::validateCoordinate(Coordinate* coord){
	if (coord->getX() < 0 || coord->getX() >= size_x){
		return false;
	}
	if (coord->getY() < 0 || coord->getY() >= size_y){
		return false;
	}
	return true;
}

Tile* GameMap::getTileAtPos(Coordinate *pos){
	if (pos->getX() < size_x && pos->getY() < size_y && pos->getX() >= 0 && pos->getY() >= 0){
		return &map[pos->getY()][pos->getX()];
	}
	return nullptr;
}

Tile* GameMap::getTileAtPos(int x, int y){
	if (x < size_x && y < size_y && x >= 0 && y >= 0){
		return &map[x][y];
	}
	return nullptr;
}

bool GameMap::newMove(Coordinate *orig, Coordinate *dest){
	Tile *orig_tile = getTileAtPos(orig);
	Tile *dest_tile = getTileAtPos(dest);

	if (orig_tile != nullptr && dest_tile != nullptr){
		q.push(new Move(orig_tile, dest_tile, dest));
		return true;
	}
	return false;
}

bool GameMap::newPickUp(Coordinate *pos){
	Tile *tile = getTileAtPos(pos);

	if (tile != nullptr){
		q.push(new Pickup(tile));
		return true;
	}
	return false;
}

bool GameMap::newMeleeAttack(Actor* attacker, Actor* target){
	
	if (attacker != nullptr && target != nullptr){
		Coordinate *attack_pos = &attacker->pos;
		Coordinate *target_pos = &target->pos;
		bool adj = isAdjacent(attack_pos, target_pos);
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
	Action* action;
	while (!q.empty()){
		action = q.front();
		result = action->execute();
		q.pop();
		delete action;
	}
}

void GameMap::resetVisibility(){
	for (int i = 0; i < size_x; i++){
		for (int j = 0; j < size_y; j++){
			map[i][j].VISIBLE = false;
		}
	}
}

bool GameMap::isAdjacent(Coordinate* orig, Coordinate* dest){
	if (abs(orig->getX() - dest->getX()) == 1){
		if (abs(orig->getY() - dest->getY()) == 0){
			return true;
		}
	}
	else if (abs(orig->getX() - dest->getX()) == 0){
		if (abs(orig->getY() - dest->getY()) == 1){
			return true;
		}
	}
	return false;
}

vector<Coord> GameMap::getNeighbors(int pos_x, int pos_y){
	vector<Coord> neighbors;
	int new_x, new_y = -1;
	for (int i = 0; i < 3; i++){ //8 potential neighbors depending on location plus origin
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