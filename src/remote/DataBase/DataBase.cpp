// 2021/04/02 17:14:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "SQLite/src/sqlite3.h"


static int callback(void * /*NotUsed*/, int argc, char **argv, char **azColName) {
    int i;

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

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

    char *sql = "CREATE TABLE COMPANY("    \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "AGE            INT     NOT NULL," \
        "ADDRESS        CHAR(50),"         \
        "SALARY         REAL );";

    char *zErrMsg = 0;

    if (sqlite3_exec(db, sql, callback, 0, &zErrMsg) != SQLITE_OK)
    {
        LOGERRORF("SQL error: %s\n", zErrMsg);
    }

    sqlite3_close(db);

    return 0;
}
    