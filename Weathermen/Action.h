#ifndef ACTION_H
#define ACTION_H

#include <stdio.h>
#include <iostream>

using namespace std;

class Action{
protected:
	int cost;

public:
	Action();
	virtual bool execute(){
		return true;
	}
};

#endif