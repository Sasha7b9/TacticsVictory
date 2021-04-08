// 2021/04/08 22:06:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace GF
{
    String GetNameFile(const char *name);

    // Return the file's last modified time. File path relative from TVData
    unsigned GetLastModifiedTime(char *name);

    String IntToString(int value, uint length);
}
