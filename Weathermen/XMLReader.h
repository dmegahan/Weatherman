#ifndef XMLREADER_H
#define XMLREADER_H

#include <stdio.h>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>

#include "Entity.h"

using namespace std;

class XMLReader{
public:
	bool readFile(string file_name);

	vector<Entity*> createEntities(string file_name);
};

#endif