#include "AI.h"

#include <time.h>
#include <cmath>

using namespace std;

AI::AI(Actor *actor, Map *map){
	this->actor = actor;
	this->map = map;
}

void AI::nextAction(){
	//viewed_tiles.clear();
	FOV();
	vector<std::array<int, 2>> moveable_tiles;

	vector < std::array<int, 2>>::iterator beg = viewed_tiles.begin();
	vector < std::array<int, 2>>::iterator end = viewed_tiles.end();
	/*
	sort(beg, end);
	beg = viewed_tiles.begin();
	end = viewed_tiles.end();
	viewed_tiles.erase(unique(beg, end), end);
	*/
	for (int i = 0; i < viewed_tiles.size(); i++){
		if (map->isAdjacent(actor->x, actor->y, viewed_tiles[i][0], viewed_tiles[i][1])){
			Tile* tile = map->getTileAtPos(viewed_tiles[i][0], viewed_tiles[i][1]);
			if (tile->isPassable() && tile->isEmpty()){
				moveable_tiles.push_back(viewed_tiles[i]);
			}
		}
	}

	srand(time(NULL));
	if (moveable_tiles.size() > 0){
		std::array<int, 2> pos = moveable_tiles.at(rand() % moveable_tiles.size());
		map->newMove(actor->x, actor->y, pos[0], pos[1]);
		actor->actionEffects();
	}
	actor->actionEffects();
}

void AI::behavior(){

}

void AI::DoFOV(float x, float y){
	int i;
	float ox, oy;
	ox = (float)actor->x + 0.5f;
	oy = (float)actor->y + 0.5f;
	for (i = 0; i < actor->view_radius; i++){
		Tile* tile = map->getTileAtPos((int)ox, (int)oy);
		if (tile != nullptr){
			std::array<int, 2> pos = { (int)ox, (int)oy };
			//tile->setColor(100, 0, 5, 0);
			viewed_tiles.push_back(pos);
			//printf("VISIBLE: x: %d, y: %d\n", (int)ox, (int)oy);
			if (!tile->isPassable() && tile->isEmpty()){
				return;
			}
			ox += x;
			oy += y;
		}
	}
	//printf("\n");
}

void AI::FOV(){
	float x, y;
	int i;
	//viewed_tiles.clear();
	//used for drawing part of the map
	//glutClass.setPlayerPos(player->x, player->y);
	for (i = 0; i < 360; i++){
		x = cos((float)i*0.01745f);
		y = sin((float)i*0.01745f);
		DoFOV(x, y);
	}
}
