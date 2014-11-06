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

using namespace std;

#define MAP_SIZEX 15
#define MAP_SIZEY 15

#define VIEW_RADIUS 5

int playerX, playerY;
Map map;
GlutClass glutClass;
vector<Actor*> all_actors;

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
	glTranslatef(-5, 4, -10);
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
	for (i = 0; i < VIEW_RADIUS; i++){
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

void keyOperations(void) {
	//def needs cleanup, keys pressed should call a certain method/object (aka movement object that calls execute)

	//When a key is pressed, add a action to the queue
	//then execute that queue (AI will add moves to it as well) and update map and call display
	if (keyStates['w']) {
		map.newMove(player->x, player->y, player->x, player->y - 1);
		cout << "w pressed!";
	}
	else if (keyStates['a']){
		map.newMove(player->x, player->y, player->x - 1, player->y);
		cout << "a pressed!";
	}
	else if (keyStates['s']){
		map.newMove(player->x, player->y, player->x, player->y + 1);
		cout << "s pressed!";
	}
	else if (keyStates['d']){
		map.newMove(player->x, player->y, player->x + 1, player->y);
		cout << "d pressed!";
	}
	else if (keyStates['z']){
		cout << "z pressed!";
	}

	for (int i = 0; i < all_actors.size(); i++){
		Actor *actor = all_actors[i];
		map.newMove(actor->x, actor->y, actor->x + 1, actor->y);

	}

	map.executeQueue();
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

	playerX = 5;
	playerY = 3;

	player = new Actor(5, 3, "PC", "Player Character", "PLAYER", '@');

	//all_actors.push_back(player);

	map.createMap();

	glutClass.InitializeTiles();

	map.getTileAtPos(playerX, playerY)->addActor(player);
	map.getTileAtPos(0, 3)->spawnItem();

	Actor *test = new Actor(1, 1, "Dave", "Dave", "Dave", 'D');
	map.getTileAtPos(test->x, test->y)->addActor(test);

	all_actors.push_back(test);

	FOV();

	glutMainLoop();

	//delete player;

	return 0;
}