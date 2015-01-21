#include "Action.h"
#include "Move.h"

using namespace std;

Move::Move(Tile *_orig, Tile *_dest, int _dest_x, int _dest_y){
	orig = _orig;
	dest = _dest;

	dest_x = _dest_x;
	dest_y = _dest_y;
}

bool Move::execute(){
	//get actors at orig (only one allowed at time of writing but may need to change (step 2) thought)
	vector<Actor*> actors = orig->getActors();
	//check if dest is empty (since only 1 allowed/shown at a time)

	bool dest_isEmpty = dest->isEmpty();

	//if no actors, return
	if (actors.empty()){
		return false;
	}
	if (!dest_isEmpty){
		return false;
	}

	if (!dest->isPassable()){
		return false;
	}

	orig->removeActor(actors[0]);
	dest->addActor(actors[0]);

	actors[0]->x = dest_x;
	actors[0]->y = dest_y;

	return true;
}