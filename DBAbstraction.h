#pragma once
#include <string>
#include "sqlite3.h"

using namespace std;

class DBAbstraction
{
public:
	DBAbstraction(string pathToFile);
	~DBAbstraction();

protected:
	//pointer to the db
	sqlite3* db;

	//private helpers to execute queries
	bool executeQueryNoResultsBack(sqlite3_stmt* myStatement);
	bool executeQueryNoResultsBack(string sql);
	bool prepareQueryWithResults(string sql, sqlite3_stmt*& myStatement);
};