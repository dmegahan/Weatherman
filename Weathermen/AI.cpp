#include "AI.h"

#include <time.h>
#include <cmath>

using namespace std;

bool AI::compare_ints(int i, int j) { return i<j; }

AI::AI(Actor *actor, GameMap *map){
	this->actor = actor;
	this->g_map = map;
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
		if (g_map->isAdjacent(actor->x, actor->y, viewed_tiles[i][0], viewed_tiles[i][1])){
			Tile* tile = g_map->getTileAtPos(viewed_tiles[i][0], viewed_tiles[i][1]);
			if (tile->isPassable() && tile->isEmpty()){
				moveable_tiles.push_back(viewed_tiles[i]);
			}
		}
	}

	srand(time(NULL));
	if (moveable_tiles.size() > 0){
		std::array<int, 2> pos = moveable_tiles.at(rand() % moveable_tiles.size());
		g_map->newMove(actor->x, actor->y, pos[0], pos[1]);
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
		Tile* tile = g_map->getTileAtPos((int)ox, (int)oy);
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

/*
	return a vector of points that make a path
*/
vector<array<int, 2>> AI::make_path(map<array<int, 2>, array<int, 2>> came_from, array<int, 2> current){
	
	vector<array<int, 2>> total_path;
	total_path.push_back(current);
	while (came_from.find(current) != came_from.end()){
		current = came_from[current];
		total_path.push_back(current);
	}
	return total_path;
}

int AI::heuristic(int x1, int y1, int x2, int y2){
	return abs(x1 - x2) + abs(y1 - y2);
}

array<int, 2> AI::lowestScore(vector<array<int, 2>> open_set, map<array<int, 2>, int> scores){
	int lowest = 999;
	array<int, 2> lowest_pos;
	for each(array<int, 2> pos in open_set){
		if (scores[pos] < lowest){
			lowest = scores[pos];
			lowest_pos = pos;
		}
	}
	return lowest_pos;
}

bool AI::isEqual(array<int, 2> a1, array<int, 2> a2){
	if (a1[0] == a2[0] && a1[1] == a2[1]){
		return true;
	}
	return false;
}

vector<array<int, 2>> AI::aStarSearch(GameMap *map_obj, int orig_x, int orig_y, int dest_x, int dest_y){
	array<int, 2> start = { orig_x, orig_y };
	array<int, 2> end = { dest_x, dest_y };
	vector<array<int, 2>> closed_set;
	vector<array<int, 2>> open_set;
	map<array<int, 2>, array<int, 2>> path;
	open_set.push_back(start);
	map<array<int, 2>, int>g_score; //cost from start along best path
	map<array<int, 2>, int>f_score; //estimated total cost from start to goal

	g_score[start] = 0;
	f_score[start] = g_score[start] + heuristic(orig_x, orig_y, dest_x, dest_y);

	while (!open_set.empty()){
		array<int, 2> current = lowestScore(open_set, f_score);
		if (isEqual(current, end)){
			return make_path(path, end);
		}
		open_set.erase(remove(open_set.begin(), open_set.end(), current), open_set.end());
		closed_set.push_back(current);

		//get all neighbors at current
		vector<array<int, 2>> neighbors = map_obj->getNeighbors(current[0], current[1]);
		for each (array<int, 2> neighbor in neighbors){
			if (!map_obj->getTileAtPos(neighbor[0], neighbor[1])->isPassable()){
				continue;
			}
			//if neighbor in closed_set
			if (find(closed_set.begin(), closed_set.end(), neighbor) != closed_set.end()){
				continue;
			}
			int tentative_g_score = g_score[current] + 1;

			//if neighbor is not in openset or tentative_g_score < g_score[neighbor]
			if (find(open_set.begin(), open_set.end(), neighbor) == open_set.end() || tentative_g_score < g_score[neighbor]){
				path[neighbor] = current;
				g_score[neighbor] = tentative_g_score;
				f_score[neighbor] = g_score[neighbor] + heuristic(neighbor[0], neighbor[1], dest_x, dest_y);
				if (find(open_set.begin(), open_set.end(), neighbor) == open_set.end()){
					open_set.push_back(neighbor);
				}
			}
		}
	}
	printf("failed");
}