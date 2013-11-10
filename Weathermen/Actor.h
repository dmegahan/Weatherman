#ifndef ACTOR_H
#define ACTOR_H

#include <stdio.h>
#include <iostream>

using namespace std;

class Actor{
	private:
		string actor_name;
		string actor_description;
		string actor_type;
		char actor_symbol;
		int color [4];

	public:
		Actor();
		Actor(string name, string description, string type, char symbol);

		void setName(string name){ actor_name = name; }
		void setDescription(string description){ actor_description = description; }
		void setType(string type){ actor_type = type; }
		void setSymbol(char symbol){ actor_symbol = symbol; }
		
		void setColor();
		int * getColor(){ return color; }

		string getName(){ return actor_name; }
		string getDescription(){ return actor_description; }
		string getType(){ return actor_type; }
		char getSymbol(){ return actor_symbol; }

};

#endif