#include <stdio.h>
#include <iostream>

#include "GlutClass.h"

GlutClass::GlutClass(){

}

GlutClass::GlutClass(GameMap *_map){
	map = _map;
}

void GlutClass::InitializeTiles(){
	char text;
	for (int y = 0; y < map->getSizeY(); y++){
		for (int x = 0; x < map->getSizeX(); x++){
			Coordinate *pos = new Coordinate(x, y);
			Tile *tile = map->getTileAtPos(pos);
			/*
			if (tile->getType().compare("GRASS") == 0){
				text = ',';
			}
			else if (tile->getType().compare("WALL") == 0){
				text = '#';
			}
			*/
			text = tile->current_character;
			tile->VISIBLE = false;
			renderTile(tile, text, x, y);
			delete pos;
		}
	}
}

void GlutClass::drawTiles(){
	/*
		draws the map
		- only draws the tiles that are within the draw range of the character
	*/
	char text;
	//calculate the min and max draw range and only show those tile within those bounds
	int draw_range = 10;
	int min_range_y = player_y - draw_range;
	if (min_range_y < 0){
		min_range_y = 0;
	}
	int max_range_y = player_y + draw_range;
	if (max_range_y > map->getSizeY()-1){
		max_range_y = map->getSizeY();
	}
	int min_range_x = player_x - draw_range;
	if (min_range_x < 0){
		min_range_x = 0;
	}
	int max_range_x = player_x + draw_range;
	if (max_range_x > map->getSizeX() - 1){
		max_range_x = map->getSizeX();
	}
	for (int y = min_range_y; y < max_range_y; y++){
		for (int x = min_range_x; x < max_range_x; x++){
			Coordinate *pos = new Coordinate(x, y);
			Tile *tile = map->getTileAtPos(pos);
			text = tile->current_character;
			renderTile(tile, text, x, y);
			delete pos;
		}
	}
}

void GlutClass::renderTile(Tile *tile, char c, int posX, int posY){
	/*
		draw an individaul tile
	*/
	vector<float> color;
	//if actor on tile and visible, change tile color to actors color and set symbol to actors symbol
	if (!tile->isEmpty() && tile->VISIBLE){
		Actor *actor = tile->getActors()[0];
		color = actor->getColor();
	}
	else{
		color = tile->getColor();
	}
	if (color.empty()){
		color = { 0, 0, 0, 0 };
	}
	//color the tiles based on their color attributes
	//draw as black if not discovered
	if (!tile->discovered){
		glColor4f(0, 0, 0, 0);
	}
	//draw with full color
	else if (tile->VISIBLE){
		glColor4f(color[0], color[1], color[2], color[3]);
	}
	//if discovered but not visible, gray out the color
	else if(!tile->VISIBLE){
		glColor4f(color[0]/2, color[1]/2, color[2]/2, color[3]/2);
	}
	//draw tile at this position
	glRasterPos3f(posX - 9, -posY + 6, -10);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

void GlutClass::reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
}

void GlutClass::glutInitialize(){
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(1024, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Weatherman");

	glutReshapeFunc(reshape);
}

