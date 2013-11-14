#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "CsvReader.h"

using namespace std;

void CsvReader::readFile(string file_name){
	//reads and prints entire csv file, will probably not be used
	string value;
	ifstream file;
	file.open(file_name);
	if(file.fail()){
		cerr << "Failure to open " + file_name << endl;
		exit(1);
	}
	getline(file, value); //skip first line
	while(file.good()){
		getline(file, value, '\n');
		cout << string(value, 0, value.length());
	}
}

std::vector<std::string> CsvReader::findName(string file_name, string name){
	string value;
	ifstream file;
	file.open(file_name);
	vector<string> vec;
	if(file.fail()){
		cerr << "Failure to open " + file_name << endl;
		exit(1);
	}
	getline(file, value);
	string field;
	//find first ,
	int first_delim = value.find_first_of(',');
	while(file.good()){
		//get entire line
		getline(file, value, '\n');
		//get name by first ,
		field = value.substr(0, first_delim);
		//if field = name, by value
		if(field.compare(name) == 0){
			return split(value, ',');
		}
	}
	vector<string> empty_vector;
	return empty_vector;
}

std::vector<std::string> CsvReader::split(const std::string &s, char delim){
	std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}