#include <iostream>
#include <vector>
#include <queue>

#include "Game World/Tile.h"
#include "Actors/Actor.h"
#include "Entities/Material.h"
#include "Entities/Items/Item.h"
#include "Game World/GameMap.h"
#include "Actions/Action.h"
#include "Actions/Move.h"
#include "GlutClass.h"
#include "AI/AI.h"
#include "ItemContainer.h"
#include "XMLReader.h"

#include <process.h>

using namespace std;

#define MAP_SIZEX 50
#define MAP_SIZEY 50

//default base offsets for drawing the map in the center of the screen
#define DEFAULT_BASE_X_OFFSET 8
#define DEFAULT_BASE_Y_OFFSET -6
//offsets for the drawing when the view has reached a certain edge
#define DEFAULT_LEFT_EDGE_X_OFFSET -5
#define DEFAULT_RIGHT_EDGE_X_OFFSET -32
#define DEFAULT_TOP_EDGE_Y_OFFSET 4
#define DEFAULT_BOTTOM_EDGE_Y_OFFSET 34
#define TRANSLATE_OFFSET -10

#define ENTER_KEY 13
#define ESCAPE_KEY 27

GameMap game_map;
GlutClass glutClass;
Coordinate *playerPos;
vector<Actor*> all_actors;
vector<AI*> all_AI;
Actor *player;


bool keyStates[256] = {false};

void renderTile (Tile tile, char c, int posX, int posY);
void keyOperations(void);

double dx;
char exit_key = '~';

void display(){
	/*
		Display is called constantly while running by openGL, it constantly draws the tiles and updates from the game_map object
	*/
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	//glTranslatef(-5, 4, -10);
	//x_offset and y_offset are used to keep the game_map centered in the middle of the screen
	int x_offset = -playerPos->getX() + DEFAULT_BASE_X_OFFSET;
	int y_offset = playerPos->getY() + DEFAULT_BASE_Y_OFFSET;

	int view_range = 10;
	//these if statements will be set to a default number if the edge of the game_map is seen, so no empty space is shown
	if (playerPos->getX() <= view_range){
		x_offset = DEFAULT_LEFT_EDGE_X_OFFSET;
	}
	else if (playerPos->getX() >= MAP_SIZEX - view_range){
		x_offset = DEFAULT_RIGHT_EDGE_X_OFFSET;
	}
	if (playerPos->getY() <= view_range){
		y_offset = DEFAULT_TOP_EDGE_Y_OFFSET;
	}
	else if (playerPos->getY() >= MAP_SIZEY - view_range){
		y_offset = DEFAULT_BOTTOM_EDGE_Y_OFFSET;
	}
	//positioning where the tiles are drawn
	glTranslatef(x_offset, y_offset, TRANSLATE_OFFSET);
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
	ox = (float)player->getPos()->getX() + 0.5f;
	oy = (float)player->getPos()->getY() + 0.5f;
	for (i = 0; i < player->view_radius; i++){
		Coordinate coord((int)ox, (int)oy);
		Tile* tile = game_map.getTileAtPos(&coord);
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
	game_map.resetVisibility();
	//used for drawing part of the game_map
	glutClass.setPlayerPos(player->getPos()->getX(), player->getPos()->getX());
	for (i = 0; i < 360; i++){
		x = cos((float)i*0.01745f);
		y = sin((float)i*0.01745f);
		DoFOV(x, y);
	}
}

/*
	Threaded function that will calculate all the actions of the 
	NPC AI and send them to game_map to be executed.
*/
void AIActions(void *arg){
	for (int i = 0; i < all_AI.size(); i++){
		AI *ai = all_AI[i];
		ai->nextAction();
	}
}

Tile* viewTiles(char exit_key){
	Tile *last_tile = game_map.getTileAtPos(playerPos);
	vector<float> color = last_tile->getDefaultColor();
	last_tile->setColor(color[0], color[1], color[2], color[3]);
	Tile *selected = nullptr;
	if (keyStates['w']) {
		delete playerPos;
		playerPos = new Coordinate(player->getPos()->getX(), player->getPos()->getY() - 1);
		cout << "w pressed!";
		//tile will be selected, recolor it until another tile is selected
		selected = game_map.getTileAtPos(playerPos);
		selected->setColor(255, 255, 0, 0);
	}
	else if (keyStates['a']){
		delete playerPos;
		playerPos = new Coordinate(player->getPos()->getX() - 1, player->getPos()->getY());
		cout << "a pressed!";
		//tile will be selected, recolor it until another tile is selected
		selected = game_map.getTileAtPos(playerPos);
		selected->setColor(255, 255, 0, 0);
	}
	else if (keyStates['s']){
		delete playerPos;
		playerPos = new Coordinate(player->getPos()->getX(), player->getPos()->getY() + 1);
		cout << "s pressed!";
		//tile will be selected, recolor it until another tile is selected
		selected = game_map.getTileAtPos(playerPos);
		selected->setColor(255, 255, 0, 0);
	}
	else if (keyStates['d']){
		delete playerPos;
		playerPos = new Coordinate(player->getPos()->getX() + 1, player->getPos()->getY());
		cout << "d pressed!";
		//tile will be selected, recolor it until another tile is selected
		selected = game_map.getTileAtPos(playerPos);
		selected->setColor(255, 255, 0, 0);
	}
	else if (keyStates[exit_key]){
		delete playerPos;
		playerPos = new Coordinate(player->getPos()->getX(), player->getPos()->getY());
		player->state = "normal";
		cout << "%c pressed!", exit_key;
	}
	else if (keyStates[ENTER_KEY]){
		//enter key pressed, select the tile, exit the state, and evaluate the selected tile
		selected = game_map.getTileAtPos(playerPos);
		vector<float> color = selected->getDefaultColor();
		selected->setColor(color[0], color[1], color[2], color[3]);
		delete playerPos;
		playerPos = new Coordinate(player->getPos()->getX(), player->getPos()->getY());
		player->state = "normal";
		cout << "Enter pressed!";
		return selected;
	}
	//unless a confirmation keystroke is pressed, dont return anything
	return nullptr;
}


void keyOperations(void) {
	//def needs cleanup, keys pressed should call a certain method/object (aka movement object that calls execute)

	//When a key is pressed, add a action to the queue
	//then execute that queue (AI will add moves to it as well) and update game_map and call display

	//valid_key_pressed sets to true if a key that causes an actual action is pressed 
	//(AKA no menu keys, no tile view keys, etc) cause an action to be used/cause the AI to move/do stuff
	bool valid_action = false;
	if (player->state.compare("normal") == 0){
		if (keyStates['w']) {
			Coordinate *dest = new Coordinate(playerPos->getX(), playerPos->getY() - 1);
			valid_action = game_map.newMove(player->getPos(), dest);
			player->actionEffects();
			cout << "w pressed!";
		}
		else if (keyStates['a']){
			Coordinate *dest = new Coordinate(playerPos->getX() - 1, playerPos->getY());
			valid_action = game_map.newMove(player->getPos(), dest);
			player->actionEffects();
			cout << "a pressed!";
		}
		else if (keyStates['s']){
			Coordinate *dest = new Coordinate(playerPos->getX(), playerPos->getY()+1);
			valid_action = game_map.newMove(player->getPos(), dest);
			player->actionEffects();
			cout << "s pressed!";
		}
		else if (keyStates['d']){
			Coordinate *dest = new Coordinate(playerPos->getX() + 1, playerPos->getY());
			valid_action = game_map.newMove(player->getPos(), dest);
			player->actionEffects();
			cout << "d pressed!";
		}
		else if (keyStates['e']){
			valid_action = game_map.newPickUp(player->getPos());
			player->actionEffects();
		}
		else if (keyStates['v']){
			//initialize to player pos before calling view
			playerPos = player->getPos();
			//change state to view state
			player->state = "view";
			exit_key = 'v';

		}
		else if (keyStates['k']){
			//initialize to player pos before calling view
			playerPos = player->getPos();
			player->state = "cview";
			exit_key = 'k';
		}
		else if (keyStates['z']){
			cout << "z pressed!";
		}
		else if (keyStates[ESCAPE_KEY]){
			printf("escape key pressed.");
			delete playerPos;
			delete player;
			for (std::vector<Actor*>::iterator it = all_actors.begin(); it != all_actors.end(); ++it)
			{
				delete (*it);
			}
			all_actors.clear();
			for (std::vector<AI*>::iterator it = all_AI.begin(); it != all_AI.end(); ++it)
			{
				delete (*it);
			}
			all_AI.clear();
			//dirty exit(), need to find a way to exit the glutMainLoop
		}

		if (valid_action == true){
			game_map.executeQueue();
			playerPos = player->getPos();
			HANDLE hThread = (HANDLE)_beginthread(AIActions, 0, 0);
			FOV();
		}
	}
	else{
		Tile *returned = viewTiles(exit_key);
		//apply the effect to a selected tile
		if (returned != nullptr){
			//check if selected was nullptr, if not, check the last state by looking at the exit key
			if (exit_key == 'k'){
				//combat exit_key
				//get the target from selected tile
				vector<Actor*> actors = returned->getActors();
				if (actors.size() > 0){
					Actor *target = actors[0];
					bool valid_action = game_map.newMeleeAttack(player, target);

					if (valid_action){
						game_map.executeQueue();
						playerPos = player->getPos();
						HANDLE hThread = (HANDLE)_beginthread(AIActions, 0, 0);
						FOV();
					}
				}
			}
		}
	}
}	

int main(int argc, char **argv){
	game_map = GameMap(MAP_SIZEX, MAP_SIZEY);
	glutClass = GlutClass(&game_map);

	glutInit(&argc, argv);
	glutClass.glutInitialize();

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);

	glutIgnoreKeyRepeat(1);

	player = new Actor(1, 2, "PC", "Player Character", "PLAYER", '@');

	playerPos = player->getPos();

	//all_actors.push_back(player);

	game_map.createMap();

	glutClass.InitializeTiles();

	Coordinate coord1(0, 3);
	game_map.getTileAtPos(playerPos)->addActor(player);
	game_map.getTileAtPos(&coord1)->spawnItem();

	Actor *test = new Actor(1, 1, "Dave", "Dave", "Dave", 'D');
	AI *test_AI = new AI(test, &game_map);

	game_map.getTileAtPos(test->getPos())->addActor(test);

	all_actors.push_back(test);
	all_AI.push_back(test_AI);

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

	Item* item1 = new Item("test1", "test1", "test1", 'U', 0);
	Item* item2 = new Item("test2", "test2", "test2", 'X', 0);

	Coordinate coord(1, 4);
	game_map.getTileAtPos(&coord)->addItem(item1);
	game_map.getTileAtPos(&coord)->addItem(item2);

	XMLReader reader;
	vector<Armor*> items = reader.readFile("Items.xml");

	Coordinate coord2(1, 6);
	game_map.getTileAtPos(&coord2)->addItem(items[0]);

	FOV();

	glutMainLoop();

	//delete player;

	return 0;
}