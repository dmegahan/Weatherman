#include "Engine.h"

Coordinate* playerPos;
GlutClass glutClass;
Engine engine;
bool keyStates[256] = { false };

void display(){
	/*
	Display is called constantly while running by openGL, it constantly draws the tiles and updates from the game_map object
	*/
	playerPos = engine.getPlayerPos();
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
	glutClass.setPlayerPos(playerPos->getX(), playerPos->getY());
	glutClass.drawTiles();
	glutSwapBuffers();
	glFlush();
}

void keyPressed(unsigned char key, int x, int y){
	keyStates[key] = true;
	engine.keyOperations();
}

void keyUp(unsigned char key, int x, int y){
	keyStates[key] = false;
}

void idle(){
	glutPostRedisplay();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	playerPos = new Coordinate(0, 0);
	engine = Engine(keyStates, playerPos);
	GameMap map = engine.initializeEngine();
	glutClass = GlutClass(&map);
	
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	engine.startEngine();

	return 0;
}