#include <GL/glew.h>
#include <Windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <array>

#include "Tile.h"
#include "Actor.h"

using namespace std;

#define MAP_SIZEX 10
#define MAP_SIZEY 10

int playerX, playerY;

bool keyStates[256] = {false};

void renderTile (Tile tile, char c, int posX, int posY);
void keyOperations(void);

Tile **tMap;
Actor *player;

Tile** createMap(){
	Tile **map;
	map = new Tile*[MAP_SIZEX];
	for (int i = 0; i < MAP_SIZEX; i++){
		map[i] = new Tile[MAP_SIZEY];
	}
	for (int i=0; i<MAP_SIZEX; i++){
		for (int j=0; j<MAP_SIZEY; j++){
			if (i%2==0 && j%2==0){
				map[i][j] = Tile("WALL", "ROCK", 2, "ROCK WALL", "ROCK WALL", false);
			}else{
				map[i][j] = Tile("GRASS", "GRASS", 0, "GRASS", "GRASS", true);
			}
		}
	}
	return map;
}

void drawTiles(){
	char text;
	for(int i = 0; i < MAP_SIZEX; i++){
		for(int j = 0; j < MAP_SIZEY; j++){
			if(tMap[i][j].hasActor(player) == true){
				text = player->getSymbol();
			}else if(tMap[i][j].isEmpty() == false){
				text = tMap[i][j].getActors()[0]->getSymbol();
			}else if (tMap[i][j].getType().compare("GRASS") == 0){
				text = ',';
			}else if(tMap[i][j].getType().compare("WALL") == 0){
				text = '#';
			}
			renderTile(tMap[i][j], text, i, j);
		}
	}
}

void FreeTexture(GLuint texture){
	glDeleteTextures(1, &texture);
}

void renderTile (Tile tile, char c, int posX, int posY){
	int *color;
	if (tile.isEmpty() == false){
		Actor *actor = tile.getActors()[0];
		color = actor->getColor();
	}else{
		color = tile.getColor();
	}
	glColor4f(color[0], color[1], color[2], color[3]);
	glRasterPos3f(posY, -posX, -5);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

void display (void){
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glTranslatef(-5, 4, -10);
	drawTiles();
	glutSwapBuffers();
	glFlush();
}

void reshape (int width, int height) {  
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
}

void keyPressed (unsigned char key, int x, int y){
	keyStates[key] = true;
	keyOperations();
}

void keyUp (unsigned char key, int x, int y){
	keyStates[key] = false;
}

void keyOperations(void) {
	int oldPlayerX = playerX;
	int oldPlayerY = playerY;
	if (keyStates['w']) {
		playerX--;
		cout << "w pressed!";
	}else if (keyStates['a']){
		playerY--;
		cout << "a pressed!";
	}else if (keyStates['s']){
		playerX++;
		cout << "s pressed!";
	}else if (keyStates['d']){
		playerY++;
		cout << "d pressed!";
	}else if (keyStates['z']){
		cout << "z pressed!";
	}
	
	try{
		if (tMap[playerX][playerY].isPassable()){
			tMap[oldPlayerX][oldPlayerY].removeActor(player);
			tMap[playerX][playerY].addActor(player);
		}else{
			playerX = oldPlayerX;
			playerY = oldPlayerY;
		}
	}catch (const std::out_of_range& oor){
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}
}
 
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition (100,100);
	glutCreateWindow("Weatherman");

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);

	glutIgnoreKeyRepeat(1);

	player = new Actor("PC", "Player Character", "PLAYER", '@');

	playerX = 5;
	playerY = 4;

	tMap = createMap();

	tMap[playerX][playerY].addActor(player);
	//cout << tMap[playerX][playerY].hasContains(player);
	//tMap[playerX][playerY].removeContains(player);
	tMap[0][1].spawnActor();

	glutMainLoop();

	//delete player;

	return 0;
}