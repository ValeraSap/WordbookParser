#pragma once
#include "sqlite3.h" //????
#include <iostream>
#include <string>


class DbHandler
{

public:

	void insertLine(std::string, std::string);
	void readLine(std::string);

	DbHandler();
	~DbHandler();
	
private: 

		sqlite3* db = 0;
		char* err = 0;
		static int callback(void* notUsed, int argc, char** argv, char** azColName);
		
	   const char* DBNAME = "wordbook.db";
	   const char* CREATE = "CREATE TABLE IF NOT EXISTS words( \
		   _id integer primary key autoincrement, \
		  spell text, \
		  mean text);";
	   const char* SELECT_ALL = "SELECT * FROM words;";
	};

