#ifndef XMLREADER_H
#define XMLREADER_H

#include <stdio.h>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>

#include "Entity.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"

using namespace std;

class XMLReader{
public:
	bool readFile(string file_name);

	Item* serializeItem(rapidxml::xml_node<>* node);
	Armor* serializeArmor(rapidxml::xml_node<>* node);
	Weapon* serializeWeapon(rapidxml::xml_node<>* node);
};

#endif