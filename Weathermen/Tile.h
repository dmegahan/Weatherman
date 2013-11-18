#ifndef TILE_H
#define TILE_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <vector>

#include "Actor.h"
#include "Item.h"
#include "Material.h"

using namespace std;

class Tile
{
	private:
		string terrain_type;
		bool is_passable;
		string name;
		string description;
		Material terrain_material;
		int height;
		std::vector<Actor*> contains_actors;
		std::vector<Item*> contains_items;
		int color [4];
	public:
		Tile();
		Tile(string type, string material, int height, string name, string description, bool passable);
		void removeActor(Actor *actor);
		bool hasActor(Actor *actor);
		void removeItem(Item *item);
		bool hasItem(Item *item);
		void spawnActor();
		void spawnItem();
		bool isEmpty();
		void addActor(Actor *actor);
		void addItem(Item *item);

		void setColor();
		int * getColor(){ return color; }

		void setType(string type){ terrain_type = type; }
		void setPassable(bool passable){ is_passable = passable; }
		void setName(string tile_name){ name = tile_name; }
		void setDescription(string tile_description){ description = tile_description; }
		void setMaterial(Material material){ terrain_material = material; }
		void setHeight(int tile_height){ height = tile_height; }

		vector<Actor*> getActors(){ return contains_actors; }
		vector<Item*> getItems(){ return contains_items; }
		string getType(){ return terrain_type; } 
		bool isPassable(){ return is_passable; }
		string getName(){ return name; }
		string getDescription(){ return description; }
		Material getMaterial(){ return terrain_material; }
		int getHeight(){ return height; }
};

#endif