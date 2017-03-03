#pragma once
#include "GUI/Controls/WindowRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WindowMenu : public WindowRTS
{
    URHO3D_OBJECT(WindowMenu, WindowRTS)

public:
    WindowMenu(Context *context = gContext);
    void Open();
    void Close();

protected:
    PODVector<ButtonRTS*> buttons;

    void SendEventReturn();
    void SetFocusedNext();                                  // Установить фокус на следующую кнопку
    void SetFocusedPrev();                                  // Установить фокус на предыдущую кнопку
    int NumFocusedButton();                                 // Возвращает номер сфокусированной кнопки. Если фокус не установлен, возвращает 0
    virtual void HandleKeyDown(StringHash, VariantMap&);    // Обработчик нажатий клавиш при открытом меню
};

