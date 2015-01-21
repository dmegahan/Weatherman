#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdio.h>
#include <iostream>

using namespace std;

class Coordinate{
private:
	int x;
	int y;

public:
	Coordinate();
	Coordinate(int x, int y);
	
	int getX(){ return this->x; }
	int getY(){ return this->y; }
};

#endif
