#pragma once
#include "GUI/Controls/WindowRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WindowMenu : public WindowRTS
{
    URHO3D_OBJECT(WindowMenu, WindowRTS)

public:
    WindowMenu(Context *context = gContext, WindowMenu *prev = nullptr);
    void Open();
    void Close();
    void ProcessingKey(int key);

protected:
    PODVector<ButtonRTS*> buttons;
    WindowMenu *prevMenu = nullptr;                         // Если при закрытии этого меню нужно отрывать предыдущее, то указатель на него хранится здесь.

    void SendEventClose();                                  // Посылается окном при его закрытии
    void SetFocusedNext();                                  // Установить фокус на следующую кнопку
    void SetFocusedPrev();                                  // Установить фокус на предыдущую кнопку
    int NumFocusedButton();                                 // Возвращает номер сфокусированной кнопки. Если фокус не установлен, возвращает 0
};

