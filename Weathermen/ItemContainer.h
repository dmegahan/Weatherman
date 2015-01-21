#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include <stdio.h>
#include <iostream>
#include <vector>

#include "Entities/Items/Item.h"

using namespace std;

class ItemContainer{
protected:
	vector<Item*> inventory;
public:
	ItemContainer();
	ItemContainer(vector<Item*>items);

	void addItems(vector<Item*>items);

	void removeItems(vector<Item*>items);
	vector<Item*> removeAllItems();
};

#endif