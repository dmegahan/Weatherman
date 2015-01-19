#include "Coordinate.h"

Coordinate::Coordinate(){
	this->x = -1;
	this->y = -1;
}

Coordinate::Coordinate(int x, int y){
	this->x = x;
	this->y = y;
}

int Coordinate::getX(){
	return this->x;
}

int Coordinate::getY(){
	return this->y;
}