#include "AI.h"

#include <time.h>
#include <cmath>
#include <list>

using namespace std;

bool AI::compare_ints(int i, int j) { return i<j; }

AI::AI(Actor *actor, GameMap *map){
	this->actor = actor;
	this->g_map = map;
}

AI::~AI(){
	//clean up the viewed_tiles list of pointers
	deleteVectorOfPointers(viewed_tiles);
	//clean up the current_path list of pointers
	for (std::deque<Coordinate*>::iterator it_current_path = current_path.begin(); it_current_path != current_path.end(); ++it_current_path)
	{
		delete (*it_current_path);
	}
	current_path.clear();
}

void AI::deleteVectorOfPointers(vector<Coordinate*> vector){
	for (std::vector<Coordinate*>::iterator it = vector.begin(); it != vector.end(); ++it)
	{
		delete (*it);
	}
	vector.clear();
}

void AI::remove_duplicate_from_vector(vector<array<int, 2>> vec, array<int, 2> item){
	vector < std::array<int, 2>>::iterator beg = vec.begin();
	vector < std::array<int, 2>>::iterator end = vec.end();
	sort(beg, end);
	beg = vec.begin();
	end = vec.end();
	vec.erase(unique(beg, end), end);
}

void AI::nextAction(){
	viewed_tiles.clear();
	FOV();

	//check if current tile has any items
	Coordinate *current_pos = actor->getPos();
	Tile* current_tile = g_map->getTileAtPos(current_pos);
	if (!current_tile->getItems().empty()){
		g_map->newPickUp(current_pos);
		return;
	}

	if (!current_path.empty()){
		Coordinate *next_move = current_path.back();
		current_path.pop_back();
		g_map->newMove(current_pos, next_move);
		return;
	}
	//coordinates of tiles that the actor can move to
	vector<Coordinate*> moveable_tiles;
	
	//coordinates of seen items/actors
	vector<Coordinate*> items_seen;
	vector<Coordinate*> actors_seen;

	vector <Coordinate*>::iterator beg = viewed_tiles.begin();
	vector <Coordinate*>::iterator end = viewed_tiles.end();
	sort(beg, end); //invalid operator here
	beg = viewed_tiles.begin();
	end = viewed_tiles.end();
	viewed_tiles.erase(unique(beg, end), end);

	//look for points of interest and available tiles to move to
	for (int i = 0; i < viewed_tiles.size(); i++){
		Tile* tile = g_map->getTileAtPos(viewed_tiles[i]);
		if (g_map->isAdjacent(current_pos, viewed_tiles[i])){
			if (tile->isPassable() && tile->isEmpty()){
				moveable_tiles.push_back(viewed_tiles[i]);
			}
		}
		if (!tile->getItems().empty()){
			Coordinate* seen_item = viewed_tiles[i];
			items_seen.push_back(seen_item);
		}
		if (!tile->getActors().empty()){
			Coordinate* seen_actor = viewed_tiles[i];
			actors_seen.push_back(seen_actor);
		}
	}
	
	//if item seen
	if (!items_seen.empty()){
		//this is where we would compare the value between items
		//map path to item
		Coordinate* dest = items_seen[0];
		current_path = aStarSearch(g_map, actor->getPos()->getX(), actor->getPos()->getY(), dest->getX(), dest->getY());
		//move to first location and pop it from vector current path
		//because it needs to do a move that turn
		Coordinate* next_move = current_path.back();
		current_path.pop_back();
		g_map->newMove(actor->getPos(), next_move);
		return;
	}

	//seed
	srand(time(NULL));
	//random movement based on adjacent tiles
	if (moveable_tiles.size() > 0 && current_path.empty()){
		Coordinate* pos = moveable_tiles.at(rand() % moveable_tiles.size());
		g_map->newMove(actor->getPos(), pos);
	}
	actor->actionEffects();
}

void AI::behavior(){

}

void AI::DoFOV(float x, float y){
	int i;
	float ox, oy;
	ox = (float)actor->pos.getX() + 0.5f;
	oy = (float)actor->pos.getY() + 0.5f;
	for (i = 0; i < actor->view_radius; i++){
		Coordinate *pos = new Coordinate((int)ox, (int)oy);
		Tile* tile = g_map->getTileAtPos(pos);
		if (tile != nullptr){
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
std::deque<Coordinate*> AI::make_path(map<Coordinate*, Coordinate*> came_from, Coordinate* current){
	std::deque<Coordinate*> total_path;
	total_path.push_back(current);
	while (came_from.find(current) != came_from.end()){
		current = came_from[current];
		total_path.push_back(current);
	}
	return total_path;
}

Coordinate* AI::lowestScore(vector<Coordinate*> open_set, map<Coordinate*, int> scores){
	int lowest = 999;
	Coordinate* lowest_pos;
	for each(Coordinate* pos in open_set){
		if (scores[pos] < lowest){
			lowest = scores[pos];
			lowest_pos = pos;
		}
	}
	return lowest_pos;
}

bool AI::isEqual(Coordinate *a1, Coordinate *a2){
	if (a1->getX() == a2->getX() && a1->getY() == a2->getY()){
		return true;
	}
	return false;
}

std::deque<Coordinate*> AI::aStarSearch(GameMap *map_obj, int orig_x, int orig_y, int dest_x, int dest_y){
	Coordinate* start = new Coordinate(orig_x, orig_y);
	Coordinate* end = new Coordinate(dest_x, dest_y);
	vector<Coordinate*> closed_set;
	vector<Coordinate*> open_set;
	map<Coordinate*, Coordinate*> path;
	open_set.push_back(start);
	map<Coordinate*, int>g_score; //cost from start along best path
	map<Coordinate*, int>f_score; //estimated total cost from start to goal

	g_score[start] = 0;
	f_score[start] = g_score[start] + heuristic(orig_x, orig_y, dest_x, dest_y);

	while (!open_set.empty()){
		Coordinate* current = lowestScore(open_set, f_score);
		if (isEqual(current, end)){
			return make_path(path, end);
		}
		open_set.erase(remove(open_set.begin(), open_set.end(), current), open_set.end());
		closed_set.push_back(current);

		//get all neighbors at current
		vector<Coordinate*> neighbors = map_obj->getNeighbors(current->getX(), current->getY());
		for each (Coordinate* neighbor in neighbors){
			//cant move into an unpassable tile, so skip
			if (!map_obj->getTileAtPos(neighbor)->isPassable()){
				continue;
			}
			//if neighbor in closed_set
			if (find(closed_set.begin(), closed_set.end(), neighbor) != closed_set.end()){
				continue;
			}
			//1 is the distance between tiles
			int tentative_g_score = g_score[current] + 1;

			//if neighbor is not in openset or tentative_g_score < g_score[neighbor]
			if (find(open_set.begin(), open_set.end(), neighbor) == open_set.end() || tentative_g_score < g_score[neighbor]){
				path[neighbor] = current;
				g_score[neighbor] = tentative_g_score;
				f_score[neighbor] = g_score[neighbor] + heuristic(neighbor->getX(), neighbor->getY(), dest_x, dest_y);
				if (find(open_set.begin(), open_set.end(), neighbor) == open_set.end()){
					open_set.push_back(neighbor);
				}
			}
		}
	}
	//failure
	std::deque <Coordinate*> empty_vec;
	return empty_vec;
}