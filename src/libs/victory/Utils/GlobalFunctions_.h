// 2021/04/08 22:06:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace GF
{
    namespace Timer
    {
        // �������� ��������� ������ ���������
        void TimeStart();

        // ���������� ����� � �������������, ��������� � ������� ������ TimeStart();
        int64 DeltaMS();

        // ������� ����� � �������������
        int64 TimeMS();
    };

    void DelayMS(uint delay);

#ifdef U3D

    String IntToString(int value, uint length);

    // ���������� � address a����, ���� � ������� ���� ������ ����
    // "-address:xxxx", � port - ����� �����, ���� � ������� ���� ������ ���� "-port:xx"
    bool GetAddressPort(const Vector<String> &words, String &address, uint16 &port);


    // Return the file's last modified time. File path relative from TVData
    unsigned GetLastModifiedTime(char *name);

    String GetNameFile(const char *name);

#ifdef GRAPHICS

    void SetWindowInCenterScreen(Window *window);

    void OpenFileSelector(char *title, char *textOk, char *textCancel, const Vector<String> &filters);

#endif

#endif
}
