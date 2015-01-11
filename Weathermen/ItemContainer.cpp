#include "ItemContainer.h"

using namespace std;

ItemContainer::ItemContainer(){
	inventory.clear();
}
ItemContainer::ItemContainer(vector<Item*>items){
	inventory.clear();	
	addItems(items);
}

void ItemContainer::addItems(vector<Item*>items){
	for (int i = 0; i < items.size(); i++){
		inventory.push_back(items[i]);
	}
}

void ItemContainer::removeItems(vector<Item*>items){
	for (int i = 0; i < items.size(); i++){
		int size = inventory.size();
		for (int j = 0; j < size; j++){
			if (items[i] == inventory[j]){
				inventory.erase(inventory.begin() + j);
				j--;
				size--;
			}
		}
	}
}

vector<Item*> ItemContainer::removeAllItems(){
	vector<Item*> removed_items = inventory;
	inventory.clear();

	return removed_items;
}