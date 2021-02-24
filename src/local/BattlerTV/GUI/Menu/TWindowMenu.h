// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/TWindow_.h"


class WindowMenu : public TWindow
{
    URHO3D_OBJECT(WindowMenu, TWindow)

public:
    WindowMenu(Context *context = TheContext);
    void Open(WindowMenu *prev = nullptr);                  // prev - меню, которое запрашивает открытие
    void Close();
    void ProcessingKey(int key);

protected:
    PODVector<TButton*> buttons;
    WindowMenu *prevMenu = nullptr;                         // Если при закрытии этого меню нужно отрывать предыдущее, то указатель на него хранится здесь. //-V122

    void SendEventClose();                                  // Посылается окном при его закрытии
    void SetFocusedNext();                                  // Установить фокус на следующую кнопку
    void SetFocusedPrev();                                  // Установить фокус на предыдущую кнопку
    int NumFocusedButton();                                 // Возвращает номер сфокусированной кнопки. Если фокус не установлен, возвращает 0
};
