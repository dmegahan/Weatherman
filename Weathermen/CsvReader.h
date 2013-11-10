#ifndef CSVREADER_H
#define CSVREADER_H

#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

class CsvReader{
	private:

	public:
		CsvReader();
		void readFile(string file_name);
};

#endif