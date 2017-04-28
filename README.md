# cpp_app_using_sqlite3
Introduction
------------
This is a small application comprising of batch, shell and C++(using Sqlite) programs. This application implements a TODO LIST using the given technologies to Create, Read, Update and Delete (CRUD) transactions into the Sqlite database.

Batch -> Shell -> C++ -> Sqlite

Code Explanation
----------------
The entry point of the application is the batch program "capp_sqlite3.bat".

Batch Program

This batch program first looks for linux like environment which is necessary to run the shell programs (like Cygwin installed). Once the linux environment is found, the batch program asks for input from the user and according to the input given by the user calls the shell programs.

Shell Programs

As the name of the shell programs explains the work done by the shell programs, the shell programs basically calls the C++ programs.

showList.sh ---> showList.cpp

addList.sh ---> addList.cpp

updateList.sh ---> updateList.cpp

deleteList.sh ---> deleteList.cpp

toggleList.sh ---> toggleList.cpp

clearList.sh ---> clearList.cpp

C++(using Sqlite) Programs

Similarly, the C++ programs explains the work done by the C++ programs, the C++ programs basically do the CRUD transactions to sqlite3 database.

showList.cpp ---> If the database exist, displays the TODO LIST by reading from the Sqlite Database.

addList.cpp ---> If the database exist, it takes input item from the user and creates an item in the TODO LIST.

updateList.cpp --> If TODO item exist, changes it to complete or incomplete.

deleteList.cpp ---> If TODO item exist, deletes the item.

toggleList.cpp ---> Toggle completeness of all TODO items from complete to incomplete or from incomplete to complete.

clearList.cpp ---> Clear all completed TODO items.
 

Table Schema
------------
CREATE TABLE TODO (ID VARCHAR,TITLE VARCHAR,COMPLETE INT);

ID --> Unique id for each TODO item (time taken from system).

TITLE --> Name of TODO item

COMPLETE --> 0 for Incomplete and 1 for complete.

How to run
----------
Firstly, a linux like environment is necessary to run the shell programs (like Cygwin installed).

Then just double-click the capp_sqlite3.bat file to run the application.
