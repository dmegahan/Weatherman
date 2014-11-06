#include <stdio.h>
#include <iostream>
#include <fstream>
#include <msxml6.h>
#include <string>

#include "Material.h"
#include "CsvReader.h"

using namespace std;

void setName(string name);
void setDescription(string description);
void setType(string type);

string getName();
string getDescription();


Material::Material(){
	setName("");
	setDescription("");
	setType("");
}

Material::Material(string mat_name){
	CsvReader csvReader;
	vector<string> fields = csvReader.findName("MATERIALS.csv", mat_name);
	setName(fields[0]);
	setDescription(fields[1]);
	setType(fields[2]);
	setColor(atof(fields[3].c_str()), 
			 atof(fields[4].c_str()), 
			 atof(fields[5].c_str()), 
			 atof(fields[6].c_str()));
}

Material::Material(string name, string description, string type, int *color[4]){
	setName(name);
	setDescription(description);
	setType(type);
}

void Material::setColor(float R, float G, float B, float A){
	this->color[0] = R;
	this->color[1] = G;
	this->color[2] = B;
	this->color[3] = A;
}
void Material::setColor(){

}

void Material::toString(){
	cout << "Name: " << getName() << endl;
	cout << "Description: " << getDescription() << endl;
	cout << "Type: " << getType() << endl;
}