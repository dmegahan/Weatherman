#ifndef GlutClass_H
#define GlutClass_H

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Map.h"
#include "Tile.h"

using namespace std;

#define draw_size_x 15
#define draw_size_y 15

class GlutClass{
private:
	Map *map;
	int player_x;
	int player_y;
public:
	vector<Tile*> tiles_to_update;

	GlutClass();
	GlutClass(Map *_map);

	void InitializeTiles();

	void drawTiles();
	void drawTilesCallback();

	void FreeTexture(GLuint texture);
	void renderTile(Tile tile, char c, int posX, int posY);
	void display(void);
	static void reshape(int width, int height);

	void glutInitialize();

	void setPlayerPos(int x, int y){
		player_x = x;
		player_y = y;
	}
};
#endif