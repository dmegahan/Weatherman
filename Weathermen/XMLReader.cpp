#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <fstream>

#include "XMLReader.h"

using namespace std;

bool XMLReader::readFile(string file_name){
	/*
	pugi::xml_document doc;

	if (!doc.load_file(file_name.c_str())){
		return false;
	}
	pugi::xml_node tools = doc.child("items");

	pugi::xml_node armors = doc.child("Items");
	for (pugi::xml_node armor = armors.first_child(); armor; armor = armor.next_sibling()){
		printf("Armor:");
		for (pugi::xml_attribute attr = armor.first_attribute(); attr; attr = attr.next_attribute()){
			cout << " " << attr.name() << "=" << attr.value();
		}
	}
	*/
	rapidxml::file<> xml_file(file_name.c_str());
	rapidxml::xml_document<> document;
	document.parse<0>(xml_file.data());
	printf("done");

	return false;
}

/*
static void XMLReader::print_element_names(xmlNode * a_node)
{
	xmlNode *cur_node = NULL;
	for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE) {
			 printf("node type: Element, name: %s\n",
				cur_node->name);
			
		}
		print_element_names(cur_node->children);
	}
}

vector<Entity*> XMLReadercreateEntities(string file_name){

}
*/