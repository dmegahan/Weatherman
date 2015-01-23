#include "Action.h"
#include "Move.h"

using namespace std;

Move::Move(Tile *orig, Tile *dest, Coordinate *coord) : Action()
{
	this->orig = orig;
	this->dest = dest;

	this->dest_x = coord->getX();
	this->dest_y = coord->getY();

	delete coord;
}

Move::~Move(){

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

	Coordinate *pos = new Coordinate(dest_x, dest_y);
	actors[0]->pos = *pos;

	return true;
}