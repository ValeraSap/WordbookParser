#include "DbHandler.h"

using namespace std;

 int DbHandler::callback(
	void* notUsed,
	int argc,
	char** argv,
	char** azColName) {
	for (int i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	return 0;
}

void DbHandler::insertLine(string spell, string mean)
{
	string sql = "insert into words(spell, mean) values ('" + spell + "','" + mean + "');";
	if (sqlite3_exec(db, sql.c_str(), 0, 0, &err))
		cout << "writing error\n";
	//else cout << "record created successfully\n";

}

//эта функция для меня
void DbHandler::readLine(string spell)
{
	
	string sql = "SELECT mean FROM words WHERE spell = '"+ spell+"';";

	//https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
	sqlite3_exec(db, sql.c_str(), callback, 0, &err);
	
}

DbHandler::DbHandler()
{

	// открываем соединение
	if (sqlite3_open(DBNAME, &db)) {
		fprintf(stderr, "Ошибка открытия/создания БД: %s\n", sqlite3_errmsg(db));
	}

	// выполняем SQL
	else if (sqlite3_exec(db, CREATE, 0, 0, &err))
	{
		fprintf(stderr, "Ошибка SQL: %sn", err);
		sqlite3_free(err);
	}
}

DbHandler::~DbHandler()
{
	sqlite3_close(db);
}
