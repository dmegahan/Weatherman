#include <stdio.h>
#include <iostream>

#include "GlutClass.h"

GlutClass::GlutClass(){

}

GlutClass::GlutClass(Map *_map){
	map = _map;
}

void GlutClass::FreeTexture(GLuint texture){
	glDeleteTextures(1, &texture);
}

void GlutClass::InitializeTiles(){
	char text;
	for (int y = 0; y < map->getSizeY(); y++){
		for (int x = 0; x < map->getSizeX(); x++){
			Tile *tile = map->getTileAtPos(x, y);
			if (tile->getType().compare("GRASS") == 0){
				text = ',';
			}
			else if (tile->getType().compare("WALL") == 0){
				text = '#';
			}
			tile->VISIBLE = false;
			renderTile(*tile, text, x, y);
		}
	}
}

void GlutClass::drawTiles(){
	char text;
	for (int y = 0; y < map->getSizeY(); y++){
		for (int x = 0; x < map->getSizeX(); x++){
			Tile *tile = map->getTileAtPos(x, y);
			text = tile->current_character;
			renderTile(*tile, text, x, y);
		}
	}
}

void GlutClass::renderTile(Tile tile, char c, int posX, int posY){
	float *color;
	if (!tile.isEmpty() && tile.VISIBLE){
		Actor *actor = tile.getActors()[0];
		color = actor->getColor();
	}
	else{
		color = tile.getColor();
	}
	if (!tile.discovered){
		glColor4f(0, 0, 0, 0);
	}
	else if (tile.VISIBLE){
		glColor4f(color[0], color[1], color[2], color[3]);
	}
	else if(!tile.VISIBLE){
		glColor4f(color[0]/2, color[1]/2, color[2]/2, color[3]/2);
	}
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

