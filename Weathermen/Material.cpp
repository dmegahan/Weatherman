#include <stdio.h>
#include <iostream>
#include <fstream>
#include <msxml6.h>

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
}

Material::Material(string name, string description, string type, int *color[4]){
	setName(name);
	setDescription(description);
	setType(type);
}

void Material::setColor(int R, int G, int B, int A){
	this->color[0] = R;
	this->color[1] = G;
	this->color[2] = B;
	this->color[3] = A;
}
void Material::setColor(){

}