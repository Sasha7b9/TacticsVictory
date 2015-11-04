#pragma once


#include "GUI/Elements/Window.h"


class MenuMain : public lWindow
{
    OBJECT(MenuMain);

public:
    MenuMain(UContext *context = gContext);

    static void RegisterObject(UContext *context = gContext);

private:
    MenuMain& operator=(const MenuMain&)
    {};

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);

    SharedPtr<ButtonMain> buttonNewGame;
    SharedPtr<ButtonMain> buttonEditor;
    SharedPtr<ButtonMain> buttonExit;
    SharedPtr<ButtonMain> buttonOptions;
    SharedPtr<ButtonSwitch> buttonLanguage;
};