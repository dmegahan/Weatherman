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
}

Tile::Tile(string type, string material, int height, string name, string description, bool passable){
	setType(type);
	setMaterial(material);
	setHeight(height);
	setName(name);
	setDescription(description);
	setPassable(passable);
	setColor();
}

void Tile::setColor(){
	/*
		Should be replaced with reading from XML file soon
	*/
	if (this->getMaterial().compare("GRASS") == 0){
		this->color[0] = 0;
		this->color[1] = 5;
		this->color[2] = 0;
		this->color[3] = 0;
	}else if (this->getMaterial().compare("ROCK") == 0){
		this->color[0] = 5;
		this->color[1] = 5;
		this->color[2] = 5;
		this->color[3] = 0;
	}
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