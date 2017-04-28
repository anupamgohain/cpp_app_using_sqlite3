#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

using namespace std;

static int showList(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for(i=1; i<argc; i++)
	{
		if(i==2)
		{
			if(atoi(argv[i])==0)
			cout<<"Incomplete";
			else if(atoi(argv[i])==1)
			cout<<"Complete";
		}
		else
		{
			cout<<"\t"<<(argv[i] ? argv[i] : "NULL")<<"\t";
		}
	}
	cout<<endl;
	return 0;
}

int main(int argc, char* argv[])
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	char *sql;

	/* Open database */
	rc = sqlite3_open("shell/cpp/data/sqlite3_database.db", &db);
	if( rc )
	{
		cout<<"Can't open database: "<<sqlite3_errmsg(db)<<endl;
		return(0);
	}

	sql = "SELECT * FROM TODO;"; 

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, showList, 0, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		cout<<"SQL error: "<<zErrMsg<<endl;
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);
	return 0;
}
