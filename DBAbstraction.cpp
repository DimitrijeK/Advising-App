#include <iostream>
#include "DBAbstraction.h"
#include "sqlite3.h"

using namespace std;

DBAbstraction::DBAbstraction(string pathToFile)
{
    //attempt to open the database
    int statusOfOpen = sqlite3_open(pathToFile.c_str(), &db);

    //if the open was NOT successful
    if (statusOfOpen != SQLITE_OK)
    {
        //make sure the db pointer is null
        db = NULL;
    }
    //else- the pointer is pointing to an open database
}
//--
DBAbstraction::~DBAbstraction()
{
    //if the db pointer points to an open db
    if (db != NULL)
    {
        //close  the database
        sqlite3_close(db);

        //make sure the db pointer is null from here on out
        db = NULL;
    }
}
//--
bool DBAbstraction::executeQueryNoResultsBack(sqlite3_stmt* myStatement)
{
    //assume there was a problem executing the query
    bool retVal = false;

    //execute the query with the step function
    int statusOfStep = sqlite3_step(myStatement);

    //SQLITE_DONE for queries that don't return a value
    if (statusOfStep == SQLITE_DONE)
    {
        retVal = true;
    }

    //clean up and destroy the statement
    sqlite3_finalize(myStatement);

    //return the success of the query
    return retVal;
}
//--
bool DBAbstraction::executeQueryNoResultsBack(string sql)
{
    //cout<<"\t"<<sql<<endl;
    //assume there was a problem executing the query
    bool retVal = false;

    //create a statement pointer
    sqlite3_stmt* myStatement;

    //create the statement object using the prepare()
    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    //check to see if the prepared statement was created
    if (statusOfPrep == SQLITE_OK)
    {
        //execute the query and get a result back
        retVal = executeQueryNoResultsBack(myStatement);
    }

    //return the success of the query
    return retVal;
}
//--
bool DBAbstraction::prepareQueryWithResults(string sql, sqlite3_stmt*& myStatement)
{
    //cout<<"\t"<<sql<<endl;
    //assume there was a problem executing the query
    bool retVal = false;

    //create the statement object using the prepare()
    int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

    //check to see if the prepared statement was created
    if (statusOfPrep == SQLITE_OK)
    {
        retVal = true;
    }

    //return the success of the query
    return retVal;
}



