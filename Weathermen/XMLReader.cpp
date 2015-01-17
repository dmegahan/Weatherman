#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <fstream>

#include "XMLReader.h"

using namespace std;

bool XMLReader::readFile(string file_name){
	rapidxml::file<> xml_file(file_name.c_str());
	rapidxml::xml_document<> document;
	document.parse<0>(xml_file.data()); 
	rapidxml::xml_node<>* root_node = document.first_node("items");
	rapidxml::xml_node<>* armor_node = root_node->first_node("armors");
	vector<Armor*> all_armors;
	for (rapidxml::xml_node<>* armors = armor_node->first_node(); armors; armors = armors->next_sibling()){
		all_armors.push_back(serializeArmor(armor_node));
	}
	printf("Done!\n");
	return false;
}

Item* XMLReader::serializeItem(rapidxml::xml_node<>* node){
	node = node->first_node();
	string name = "";
	string description = "";
	string material = "";
	char symbol = '%';
	int weight = 0;

	name = node->first_attribute("name")->value();
	description = node->first_attribute("desc")->value();
	material = node->first_attribute("material")->value();
	symbol = *node->first_attribute("symbol")->value();
	weight = (int)node->first_attribute("weight")->value();

	Item *item = new Item(name, description, material, symbol, weight);

	return item;
}

Armor* XMLReader::serializeArmor(rapidxml::xml_node<>* node){
	node = node->first_node();
	string name = "";
	string description = "";
	string material = "";
	char symbol = '%';
	int weight = 0;
	string item_slot = "";
	int armor = 0;
	string type = "";

	name = node->first_attribute("name")->value();
	description = node->first_attribute("desc")->value();
	material = node->first_attribute("material")->value();
	symbol = *node->first_attribute("symbol")->value();
	weight = stoi(node->first_attribute("weight")->value());
	item_slot = node->first_attribute("item_slot")->value();
	armor = stoi(node->first_attribute("armor")->value());
	type = node->first_attribute("type")->value();

	Armor *armor_item = new Armor(name, description, material, symbol, weight, item_slot, armor, type);

	return armor_item;
}
Weapon* XMLReader::serializeWeapon(rapidxml::xml_node<>* node){
	node = node->first_node();
	string name = "";
	string description = "";
	string material = "";
	char symbol = '%';
	int weight = 0;
	string item_slot = "";
	string type = "";
	float attack_speed = 0.1;
	int attack = 0;

	name = node->first_attribute("name")->value();
	description = node->first_attribute("desc")->value();
	material = node->first_attribute("material")->value();
	symbol = *node->first_attribute("symbol")->value();
	weight = (int)node->first_attribute("weight")->value();
	item_slot = node->first_attribute("item_slot")->value();
	type = (int)node->first_attribute("weapon_type")->value();
	attack = (int)node->first_attribute("attack")->value();
	attack_speed = stof(node->first_attribute("attack_speed")->value());

	Weapon *weapon_item = new Weapon(name, description, material, symbol, weight, item_slot, type, attack, attack_speed);

	return weapon_item;
}