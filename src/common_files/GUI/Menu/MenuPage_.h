// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Window_.h"


class MenuPage : public WindowT
{
    URHO3D_OBJECT(MenuPage, WindowT)

public:
    MenuPage();
    void Open(MenuPage *prev = nullptr);                  // prev - меню, которое запрашивает открытие
    void Close();
    void ProcessingKey(int key);

protected:
    PODVector<ButtonT *> buttons;
    MenuPage *prev_menu = nullptr;                        // Если при закрытии этого меню нужно отрывать предыдущее,
                                                            // то указатель на него хранится здесь.

    void SendEventClose();                                  // Посылается окном при его закрытии
    void SetFocusedNext();                                  // Установить фокус на следующую кнопку
    void SetFocusedPrev();                                  // Установить фокус на предыдущую кнопку
    int NumFocusedButton();                                 // Возвращает номер сфокусированной кнопки. Если фокус не
                                                            // установлен, возвращает 0
};
