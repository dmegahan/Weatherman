#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "CsvReader.h"

using namespace std;

CsvReader::CsvReader(){

}

void CsvReader::readFile(string file_name){
	string value;
	ifstream file;
	file.open(file_name);
	if(file.fail()){
		cerr << "Failure to open " + file_name << endl;
		exit(1);
	}
	getline(file, value); //skip first line
	while(file.good()){
		getline(file, value, ',');
		cout << string(value, 0, value.length());
	}
}