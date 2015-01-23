#include "Action.h"
#include "Pickup.h"

using namespace std;

Pickup::Pickup(Tile *pos) : Action(){
	this->pos = pos;
}

bool Pickup::execute(){
	if (pos->getActors().size() <= 0){
		return false;
	}
	//Currently only 1 actor can be on a square at a time, so check the first one
	Actor *actor = pos->getActors()[0];
	vector<Item*> items = pos->getItems();
	if (items.size() <= 0){
		return false;
	}

	ItemContainer *inv = actor->getInventory();
	inv->addItems(items);

	pos->removeAllItems();
	return true;
}