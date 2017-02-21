#pragma once


#include "GUI/Elements/Window.h"


class ButtonSwitch;


class MenuMain : public WindowRTS
{
    URHO3D_OBJECT(MenuMain, WindowRTS);

public:
    MenuMain(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);
    void SetEnabled();
    void SetDisabled();
    void Open();
    void Close();

private:
    MenuMain& operator=(const MenuMain&)
    {};

    void HandleButtonRelease(StringHash, VariantMap&);  
    void HandleKeyDown(StringHash, VariantMap&);        // Обработчик нажатий клавиш при открытом меню

    void SetFocusedNext();                              // Установить фокус на следующую кнопку
    void SetFocusedPrev();                              // Установить фокус на предыдущую кнопку
    int NumFocusedButton();                             // Возвращает номер сфокусированной кнопки. Если фокус не установлен, возвращает 0

    PODVector<ButtonRTS*> buttons;

    SharedPtr<ButtonRTS> buttonNewGame;
    SharedPtr<ButtonRTS> buttonEditor;
    SharedPtr<ButtonRTS> buttonExit;
    SharedPtr<ButtonRTS> buttonOptions;
    SharedPtr<ButtonSwitch> buttonLanguage;
    SharedPtr<ButtonRTS> buttonCancel;
};
