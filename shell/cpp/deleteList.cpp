#include <iostream>
#include <stdlib.h>
#include <string>
#include "sqlite3.h"

using namespace std;

static void deleteList()
{
	sqlite3 *db;
	sqlite3_stmt *st;
	char *zErrMsg = 0;
	int  rc;

	/* Open database */
	rc = sqlite3_open("shell/cpp/data/sqlite3_database.db", &db);
	if( rc )
	{
		cout<<"Can't open database: "<<sqlite3_errmsg(db)<<endl;
	}
	string title;

	cout<<"Enter TODO title: ";
	cin>>title;

	string sql = "DELETE FROM TODO WHERE TITLE=?;";
	/* Execute SQL statement */
	if( rc == SQLITE_OK )
	{
		sqlite3_prepare( db, sql.c_str(), -1, &st, NULL);
        	sqlite3_bind_text(st, 1, title.c_str(), title.length(), SQLITE_TRANSIENT);
        	int step=sqlite3_step( st );cout<<"Result: "<<step<<endl;
		cout<<"Data deleted."<<endl;
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
	cout<<"DELETING TODO ITEM"<<endl;
	deleteList();
	return 0;
}
