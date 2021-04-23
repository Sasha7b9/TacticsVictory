// 2021/04/08 22:06:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace GF
{
    namespace Timer
    {
        // Засекает начальный момент измерения
        void TimeStart();

        // Возвращает время в миллисекундах, прошедшее с момента вызова TimeStart();
        int64 DeltaMS();

        // Текущее время в миллисекундах
        int64 TimeMS();
    };

    void DelayMS(uint delay);

#ifdef U3D

    std::string IntToString(int value, uint length);

    // Возвращает в address aдрес, если в векторе есть строка вида
    // "-address:xxxx", в port - адрес порта, если в векторе есть строка вида "-port:xx"
    bool GetAddressPort(const Vector<std::string> &words, std::string &address, uint16 &port);


    // Return the file's last modified time. File path relative from TVData
    unsigned GetLastModifiedTime(char *name);

    std::string GetNameFile(pchar name);

#ifdef GRAPHICS

    void SetWindowInCenterScreen(Window *window);

    void OpenFileSelector(char *title, char *textOk, char *textCancel, const Vector<std::string> &filters);

#endif

#endif
}
