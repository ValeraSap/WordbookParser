#pragma once
#include "sqlite3.h"
#include <iostream>
#include <string>
class DbHandler
{

public:

	void insertLine(std::string, std::string);
	void readLine(std::string);

	//void selectCallback(std::string mean);

	

	DbHandler();
	~DbHandler();
	
private: 

	// хэндл объекта соединение к БД
		sqlite3* db = 0;
		char* err = 0;
		static int callback(void* notUsed, int argc, char** argv, char** azColName);
		
	   const char* DBNAME = "wordbook.dblite";
	   //const char* SQL = "CREATE TABLE IF NOT EXISTS words(ID INT PRIMARY KEY NOT NULL, spell, mean);";
	   const char* CREATE = "CREATE TABLE IF NOT EXISTS words(spell, mean);";
	  // const char* INSERT = "insert into words(spell, mean) values ('%q','%q');";
	   const char* SELECT_ALL = "SELECT * FROM words;";
	 //  const char* SELECT_LINE = "SELECT mean FROM words WHERE spell = '%q';";
};

