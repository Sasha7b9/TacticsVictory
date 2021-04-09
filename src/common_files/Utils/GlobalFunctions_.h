// 2021/04/08 22:06:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace GF
{
    void DelayMS(uint delay);

    String GetNameFile(const char *name);

    // Return the file's last modified time. File path relative from TVData
    unsigned GetLastModifiedTime(char *name);

    String IntToString(int value, uint length);

    // ���������� � address a����, ���� � ������� ���� ������ ����
    // "-address:xxxx", � port - ����� �����, ���� � ������� ���� ������ ���� "-port:xx"
    bool GetAddressPort(const Vector<String> &words, String &address, uint16 &port);
}
