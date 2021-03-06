#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdio.h>
#include <iostream>

#include "../CsvReader.h"

using namespace std;

class Material{
	private:
		string material_name;
		string material_description;
		string material_type;
		float color[4];

	public:
		Material();
		Material(string mat_name);
		Material(string mat_name, string description, string type, int *color[4]);

		void setName(string name){ material_name = name; }
		void setDescription(string description){ material_description = description; }
		void setType(string type){ material_type = type; }
		
		void setColor();
		void setColor(float R, float G, float B, float A);
		float* getColor(){ return color; }

		string getName(){ return material_name; }
		string getDescription(){ return material_description; }
		string getType(){ return material_type; }

		void toString();
};

#endif
