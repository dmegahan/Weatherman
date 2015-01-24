#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <process.h>

#include "Actors/Actor.h"
#include "Entities/Material.h"
#include "Entities/Items/Item.h"
#include "Actions/Action.h"
#include "Actions/Move.h"
#include "GlutClass.h"
#include "AI/AI.h"
#include "ItemContainer.h"
#include "XMLReader.h"

#define MAP_SIZEX 50
#define MAP_SIZEY 50

#define ENTER_KEY 13
#define ESCAPE_KEY 27

using namespace std;

class Engine{
private:
	GameMap game_map;
	GlutClass glutClass;
	Actor *player;
	vector<Actor*> all_actors;
	Coordinate *playerPos;

	bool *keyStates;
	char exit_key = '~';
public:
	Engine();
	Engine(bool *keyStates, Coordinate *playerPos);
	
	GameMap initializeEngine();
	void startEngine();
	//void AIActions(void* arg);

	Tile* viewTiles(char exit_key);
	void FOV();
	void doFOV(float x, float y);
	void keyOperations(void);
	void idle();
	Coordinate* getPlayerPos();

	void setupDrawCallback();

	//static casts to function for functions that require function pointers
	/*
	static void __cdecl AIActionsWrapper(void* arg)
	{
		static_cast<Engine*>(arg)->AIActions(arg);
	}
	static void __cdecl idleWrapper()
	{
		void* arg = nullptr;
		static_cast<Engine*>(arg)->idle();
	}
	static void __cdecl keyPressedWrapper(unsigned char key, int x, int y)
	{
		void* arg = nullptr;
		static_cast<Engine*>(arg)->keyPressed(key, x, y);
	}

	static void __cdecl keyUpWrapper(unsigned char key, int x, int y)
	{
		void* arg = nullptr;
		static_cast<Engine*>(arg)->keyUp(key, x, y);
	}
	*/
};
#endif