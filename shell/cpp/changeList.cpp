#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

using namespace std;

int complete=0;
char *title=new char[20];

static int updateCallback(void *NotUsed, int argc, char **argv, char **azColName)
{
	if(atoi(argv[0])==1)
	{
		complete=0;
	}
	else if(atoi(argv[0])==0)
	{
		complete=1;
	}
	return 0;
 }

void updateList()
{
	sqlite3 *db;
	sqlite3_stmt *st;
	char *zErrMsg = 0;
	int rc;
	string sql;
	string ttitle(title);
	
	rc = sqlite3_open("shell/cpp/data/sqlite3_database.db", &db);
	if( rc )
	{
		cout<<"Can't open database: "<<sqlite3_errmsg(db)<<endl;
	}

	sql = "UPDATE TODO SET COMPLETE=? WHERE TITLE=?";

	/* Execute SQL statement */
	if( rc == SQLITE_OK )
	{
		sqlite3_prepare( db, sql.c_str(), -1, &st, NULL);
		sqlite3_bind_int(st, 1, complete);
		sqlite3_bind_text(st, 2, ttitle.c_str(), ttitle.length(), SQLITE_TRANSIENT);
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
	char *sql=new char[500];

	cout<<"UPDATING TODO LIST"<<endl;
	/* Open database */
	rc = sqlite3_open("shell/cpp/data/sqlite3_database.db", &db);
	if( rc )
	{
		cout<<"Can't open database: "<<sqlite3_errmsg(db)<<endl;
		return(0);
	}
	cout<<"Enter TODO title: ";
	cin>>title;

	strcpy (sql, "SELECT COMPLETE FROM TODO WHERE TITLE='");
	strcat (sql, title);
	strcat (sql, "';");

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, updateCallback, 0, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		cout<<"SQL error: "<<zErrMsg<<endl;
		sqlite3_free(zErrMsg);
	}
	sqlite3_close(db);
	updateList();
	delete title;
	delete sql;
	return 0;
}
