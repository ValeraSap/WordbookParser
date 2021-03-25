#pragma once

#include "DbHandler.h"
#include "parser.h"

#include <iostream>
#include <list>
#include <fstream>
#include <string>

#include <thread>
#include <iterator>
#include <utility>

#include <mutex>

using namespace std;

class FileHandler
{
public:

	void run();
	FileHandler(string,string);
	~FileHandler();

private:

	Parser parser;	
	string str;
	list <pair<string, string>> words;
	DbHandler dbHandler;

	ifstream* ifile;
	ofstream* ofile;

	void toList();
	void fromList();
};

