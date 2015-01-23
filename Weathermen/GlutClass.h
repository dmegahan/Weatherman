#ifndef GlutClass_H
#define GlutClass_H

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Game World/GameMap.h"
#include "Game World/Tile.h"

using namespace std;

#define DEFAULT_DRAW_RANGE 10
//used in the glRasterPos3f (glut function call) in renderTile
#define DEFAULT_RASTER_X_OFFSET -9
#define DEFAULT_RASTER_Y_OFFSET 6
#define DEFAULT_RASTER_Z -10

class GlutClass{
private:
	GameMap *map;
	int player_x;
	int player_y;
public:
	vector<Tile*> tiles_to_update;

	GlutClass();
	explicit GlutClass(GameMap *_map);

	void InitializeTiles();

	void drawTiles();
	void drawTilesCallback();

	void FreeTexture(GLuint texture){ glDeleteTextures(1, &texture); }
	void renderTile(Tile *tile, char c, int posX, int posY);
	void display(void);
	static void reshape(int width, int height);

	void glutInitialize();

	void setPlayerPos(int x, int y){
		player_x = x;
		player_y = y;
	}
};
#endif