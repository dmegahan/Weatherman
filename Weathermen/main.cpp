#include <iostream>
#include <vector>
#include <queue>

#include "Tile.h"
#include "Actor.h"
#include "Material.h"
#include "CsvReader.h"
#include "Item.h"
#include "Map.h"
#include "Action.h"
#include "Move.h"
#include "GlutClass.h"
#include "AI.h"
#include "ItemContainer.h"

#include <process.h>

using namespace std;

#define MAP_SIZEX 50
#define MAP_SIZEY 50

#define VIEW_RADIUS 5

int playerX, playerY;
Map map;
GlutClass glutClass;
vector<Actor*> all_actors;
vector<AI*> all_AI;

bool keyStates[256] = {false};

void renderTile (Tile tile, char c, int posX, int posY);
void keyOperations(void);

Actor *player;

int factor = 100;
double dx;

void display(){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	//glTranslatef(-5, 4, -10);
	//x_offset and y_offset are used to keep the map centered in the middle of the screen
	int x_offset = -player->x + 8; 
	int y_offset = player->y - 6;

	int view_range = 10;
	//these if statements will be set to a default number if the edge of the map is seen, so no empty space is shown
	if (player->x <= view_range){
		x_offset = -5;
	}
	else if (player->x >= MAP_SIZEX - view_range){
		x_offset = -32;
	}
	if (player->y <= view_range){
		y_offset = 4;
	}
	else if (player->y >= MAP_SIZEY - view_range){
		y_offset = 34;
	}
	glTranslatef(x_offset, y_offset, -10);
	glutClass.drawTiles();
	glutSwapBuffers();
	glFlush();
}

void idle(){
	glutPostRedisplay();
}

void keyPressed (unsigned char key, int x, int y){
	keyStates[key] = true;
	keyOperations();
}

void keyUp (unsigned char key, int x, int y){
	keyStates[key] = false;
}

void DoFOV(float x, float y){
	int i;
	float ox, oy;
	ox = (float)player->x + 0.5f;
	oy = (float)player->y + 0.5f;
	for (i = 0; i < player->view_radius; i++){
		Tile* tile = map.getTileAtPos((int)ox, (int)oy);
		if (tile != nullptr){
			tile->VISIBLE = true;
			tile->discovered = true;
			tile->setCharacter();
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

void FOV(){
	float x, y;
	int i;
	map.resetVisibility();
	//used for drawing part of the map
	glutClass.setPlayerPos(player->x, player->y);
	for (i = 0; i < 360; i++){
		x = cos((float)i*0.01745f);
		y = sin((float)i*0.01745f);
		DoFOV(x, y);
	}
}

/*
	Threaded function that will calculate all the actions of the 
	NPC AI and send them to map to be executed.
*/
void AIActions(void *arg){
	for (int i = 0; i < all_AI.size(); i++){
		AI *ai = all_AI[i];
		ai->nextAction();
	}
}



void keyOperations(void) {
	//def needs cleanup, keys pressed should call a certain method/object (aka movement object that calls execute)

	//When a key is pressed, add a action to the queue
	//then execute that queue (AI will add moves to it as well) and update map and call display
	if (keyStates['w']) {
		map.newMove(player->x, player->y, player->x, player->y - 1);
		player->actionEffects();
		cout << "w pressed!";
	}
	else if (keyStates['a']){
		map.newMove(player->x, player->y, player->x - 1, player->y);
		player->actionEffects();
		cout << "a pressed!";
	}
	else if (keyStates['s']){
		map.newMove(player->x, player->y, player->x, player->y + 1);
		player->actionEffects();
		cout << "s pressed!";
	}
	else if (keyStates['d']){
		map.newMove(player->x, player->y, player->x + 1, player->y);
		player->actionEffects();
		cout << "d pressed!";
	}
	else if (keyStates['e']){
		map.newPickUp(player->x, player->y);
		player->actionEffects();
	}
	else if (keyStates['z']){
		cout << "z pressed!";
	}

	map.executeQueue();
	HANDLE hThread = (HANDLE)_beginthread(AIActions, 0, 0);
	FOV();
}	

int main(int argc, char **argv){
	map = Map(MAP_SIZEX, MAP_SIZEY);
	glutClass = GlutClass(&map);

	glutInit(&argc, argv);
	glutClass.glutInitialize();

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);

	glutIgnoreKeyRepeat(1);

	player = new Actor(48, 49, "PC", "Player Character", "PLAYER", '@');

	playerX = player->x;
	playerY = player->y;

	//all_actors.push_back(player);

	map.createMap();

	glutClass.InitializeTiles();

	map.getTileAtPos(playerX, playerY)->addActor(player);
	map.getTileAtPos(0, 3)->spawnItem();

	Actor *test = new Actor(1, 1, "Dave", "Dave", "Dave", 'D');
	AI *test_AI = new AI(test, &map);
	map.getTileAtPos(test->x, test->y)->addActor(test);

	all_actors.push_back(test);
	all_AI.push_back(test_AI);

	FOV();
	/*
	Item* item1 = new Item("test1", "test1", "iron", 'U');
	Item* item2 = new Item();
	//Item* item3 = new Item(*item1);
	vector<Item*> items = { item1, item2};
	ItemContainer *cont = new ItemContainer(items);

	Item* item4 = new Item();
	cont->addItems({ item4 });
	cont->removeItems({ item4, item1 });
	vector<Item*> removed_items = cont->removeAllItems();
	*/

	Item* item1 = new Item("test1", "test1", "test1", 'U');
	Item* item2 = new Item("test2", "test2", "test2", 'X');

	map.getTileAtPos(1, 4)->addItem(item1);
	map.getTileAtPos(1, 4)->addItem(item2);

	glutMainLoop();

	//delete player;

	return 0;
}