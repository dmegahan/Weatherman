#include <vector>
#include <stdio.h>
#include <iostream>

#include "Tile.h"
#include "Actor.h"

using namespace std;

void setType(string type);
void setPassable(bool passable);
void setName(string tile_name);
void setDescription(string tile_description);
void setMaterial(string material);
void setHeight(int tile_height);
void addContains(Actor actor);

vector<Actor> getContains();
string getType();
bool isPassable();
string getName();
string getDescription();
string getMaterial();
int getHeight();

Tile::Tile(){
	setType("ROCK");
	setColor();
	default_character = '#';
	current_character = default_character;

	VISIBLE = false;
	discovered = false;
}

Tile::Tile(string type, string material, int height, string name, string description, bool passable){
	setType(type);
	setMaterial(Material(material));
	setHeight(height);
	setName(name);
	setDescription(description);
	setPassable(passable);
	setColor();

	if (this->getType().compare("GRASS") == 0){
		default_character = ',';
		current_character = default_character;
	}
	else if (this->getType().compare("WALL") == 0){
		default_character = '#';
		current_character = default_character;
	}

	VISIBLE = false;
	discovered = false;
}

void Tile::setColor(){
	this->color[0] = getMaterial().getColor()[0];
	this->color[1] = getMaterial().getColor()[1];
	this->color[2] = getMaterial().getColor()[2];
	this->color[3] = getMaterial().getColor()[3];
}

void Tile::removeActor(Actor *actor){
	//attempts to find actor in contains_actors
	for(int i = 0; i < this->contains_actors.size(); i++){
		if (actor == this->contains_actors[i]){
			this->contains_actors.erase(this->contains_actors.begin()+i);
		}
	}
	//if no actors, set passable to default
	if (contains_actors.empty()){
		this->setPassable(true);
	}
}

bool Tile::hasActor(Actor *actor){
	bool has_contains = false;
	for(int i = 0; i < this->contains_actors.size(); i++){
		if (actor == this->contains_actors[i]){
			has_contains = true;
		}else{
			has_contains = false;
		}
	}
	return has_contains;
}

void Tile::addActor(Actor *actor){
	this->setPassable(false);
	this->contains_actors.push_back(actor);
}

void Tile::spawnActor(){
	//filler for now, probably should move this out to an action or another case of classes
	Actor *newActor = new Actor();
	this->addActor(newActor);
}

void Tile::removeItem(Item *item){
	for(int i = 0; i < this->contains_items.size(); i++){
		if (item == this->contains_items[i]){
			this->contains_items.erase(this->contains_items.begin()+i);
		}
	}
}

bool Tile::hasItem(Item *item){
	bool has_items = false;
	for(int i = 0; i < this->contains_items.size(); i++){
		if (item == this->contains_items[i]){
			has_items = true;
		}else{
			has_items = false;
		}
	}
	return has_items;
}

void Tile::addItem(Item *item){
	this->contains_items.push_back(item);
}

void Tile::spawnItem(){
	Item *newItem = new Item();
	this->addItem(newItem);
}

bool Tile::isEmpty(){
	bool is_empty = false;
	if (this->getActors().empty()){
		is_empty = true;
	}else{
		is_empty = false;
	}
	return is_empty;
}

void Tile::setCharacter(){
	if (getType().compare("GRASS") == 0){
		current_character = ',';
	}
	else if (getType().compare("WALL") == 0){
		current_character = '#';
	}
	if (getItems().size() > 0){
		current_character = getItems()[0]->getSymbol();
	}
	if (!isEmpty()){
		current_character = getActors()[0]->getSymbol();
	}
}