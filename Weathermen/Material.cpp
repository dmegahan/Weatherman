#include <stdio.h>
#include <iostream>

#include "Material.h"

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

Material::Material(string name, string description, string type){
	setName(name);
	setDescription(description);
	setType(type);
}

Material::Material(FILE *file){

}

void Material::setColor(){

}