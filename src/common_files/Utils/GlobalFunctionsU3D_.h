// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace GFU3D
{
    void DelayMS(uint delay);
    void SetWindowInCenterScreen(Window *window);
    void OpenFileSelector(char *title, char *textOk, char *textCancel, const Vector<String> &filters);
}
