#include <iostream>
#include <stdlib.h>
#include <string>
#include "sqlite3.h"
#include <ctime>

using namespace std;

static void addList()
{
	sqlite3 *db;
	sqlite3_stmt *st;
	char *zErrMsg = 0;
	int  rc;

	time_t currentTime;
	struct tm *localTime;

	time( &currentTime );
	localTime = localtime( &currentTime );

	int Day    = localTime->tm_mday;
	int Month  = localTime->tm_mon + 1;
	int Year   = localTime->tm_year + 1900;
	int Hour   = localTime->tm_hour;
	int Min    = localTime->tm_min;
	int Sec    = localTime->tm_sec;

	/* Open database */
	rc = sqlite3_open("shell/cpp/data/sqlite3_database.db", &db);
	if( rc )
	{
		cout<<"Can't open database: "<<sqlite3_errmsg(db)<<endl;
	}
	string id=to_string(Day)+to_string(Month)+to_string(Year)+to_string(Hour)+to_string(Min)+to_string(Sec);
	string title="";
	int complete=0;

	cout<<"Enter TODO item: ";
	cin>>title;

	string sql = "INSERT INTO TODO VALUES (?,?,?);";
	/* Execute SQL statement */
	if( rc == SQLITE_OK )
	{
		sqlite3_prepare( db, sql.c_str(), -1, &st, NULL);
        	sqlite3_bind_text(st, 1, id.c_str(), id.length(), SQLITE_TRANSIENT);
        	sqlite3_bind_text(st, 2, title.c_str(), title.length(), SQLITE_TRANSIENT);
        	sqlite3_bind_int(st, 3, complete);
        	sqlite3_step( st );
		cout<<"New data inserted."<<endl;
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
	cout<<"ADDING NEW TODO ITEM"<<endl;
	addList();
	return 0;
}
