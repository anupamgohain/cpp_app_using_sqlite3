#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

int complete=0;

using namespace std;

static int toggleCallback(void *NotUsed, int argc, char **argv, char **azColName)
{
	if(atoi(argv[0])>0)
	{
		complete=1;
	}
	else if(atoi(argv[0])==0)
	{
		complete=0;
	}
	return 0;
}

void toggleList()
{
	sqlite3 *db;
	sqlite3_stmt *st;
	char *zErrMsg = 0;
	int rc;
	string sql;
	
	rc = sqlite3_open("shell/cpp/data/sqlite3_database.db", &db);
	if( rc )
	{
		cout<<"Can't open database: "<<sqlite3_errmsg(db)<<endl;
	}

	sql = "UPDATE TODO SET COMPLETE=?;";
	/* Execute SQL statement */
	if( rc == SQLITE_OK )
	{
		sqlite3_prepare( db, sql.c_str(), -1, &st, NULL);
		sqlite3_bind_int(st, 1, complete);
		int step=sqlite3_step(st);
		cout<<"Data updated."<<endl;
	}
	else
	{
		cout<<"SQL error: "<<zErrMsg<<endl;
		sqlite3_free(zErrMsg);
	}

	sqlite3_finalize(st);
	sqlite3_close(db);
}

int main(int argc, char* argv[])
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char *sql;

	cout<<"TOGGLING TODO LIST"<<endl;
	/* Open database */
	rc = sqlite3_open("shell/cpp/data/sqlite3_database.db", &db);
	if( rc )
	{
		cout<<"Can't open database: "<<sqlite3_errmsg(db)<<endl;
		return(0);
	}

	sql = "SELECT COUNT(TITLE) FROM TODO WHERE COMPLETE=0;"; 

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, toggleCallback, 0, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		cout<<"SQL error: "<<zErrMsg<<endl;
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);
	toggleList();

	return 0;
}
