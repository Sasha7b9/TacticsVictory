// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "SQLite/src/sqlite3.h"


static int callback(void *data, int argc, char **argv, char **azColName) {
    int i;

    LOGWRITE("");
    LOGWRITEF("%s: ", (pchar)data);

    for (i = 0; i < argc; i++)
    {
        LOGWRITEF("%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    return 0;
}


int main()
{
    setlocale(LC_ALL, "Russian");

    LogRAW::Create("DataBase.log", false);

    LOGWRITE("Start DataBase");

    sqlite3 *db = nullptr;

    if (sqlite3_open("db.sqlite3", &db) != 0)
    {
        LOGERRORF("Can't open database: %s", sqlite3_errmsg(db));
    }

    pchar sql = "CREATE TABLE COMPANY("    \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "AGE            INT     NOT NULL," \
        "ADDRESS        CHAR(50),"         \
        "SALARY         REAL );";

    char *zErrMsg = 0;

    if (sqlite3_exec(db, sql, callback, 0, &zErrMsg) != SQLITE_OK)
    {
        LOGERRORF("SQL error: %s", zErrMsg);
    }

    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "   \
        "VALUES (1, 'Paul', 32, 'California', 20000.00 ); "     \
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "     \
        "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "         \
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)"      \
        "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );"         \
        "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)"      \
        "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

    if (sqlite3_exec(db, sql, callback, 0, &zErrMsg) != SQLITE_OK)
    {
        LOGERRORF("SQL error: %s", zErrMsg);
    };

    sql = "SELECT * from COMPANY";

    pchar data = "Callback function called";

    if (sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg) != SQLITE_OK)
    {
        LOGERRORF("SQL error: %s", zErrMsg);
    }

    sqlite3_close(db);

    return 0;
}
    