#pragma once


#include "GUI/Elements/Window.h"


class lMenuMain : public lWindow
{
    OBJECT(lMenuMain);

public:
    lMenuMain(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

private:
    lMenuMain& operator=(const lMenuMain&)
    {};

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);

    SharedPtr<lButton> buttonNewGame;
    SharedPtr<lButton> buttonEditor;
    SharedPtr<lButton> buttonExit;
    SharedPtr<lButton> buttonOptions;
    SharedPtr<lButtonSwitch> buttonLanguage;
};