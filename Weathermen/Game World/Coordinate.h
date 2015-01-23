#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdio.h>
#include <iostream>

using namespace std;

class Coordinate{
private:

public:
	int x;
	int y;

	Coordinate();
	Coordinate(int x, int y);
	
	int getX(){ return this->x; }
	int getY(){ return this->y; }
};

#endif
