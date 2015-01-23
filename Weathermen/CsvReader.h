#ifndef CSVREADER_H
#define CSVREADER_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class CsvReader{
	public:
		void readFile(string file_name);
		std::vector<std::string> findName(string file_name, string name);
		std::vector<std::string> split(const std::string &s, char delim);
};

#endif