#pragma once


#include "GUI/Elements/Window.h"


class vMenuMain : public vWindow
{
    OBJECT(vMenuMain);

public:
    vMenuMain(Context *context);

    static void RegisterObject(Context *context);

    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);

private:
    vMenuMain& operator=(const vMenuMain&)
    {};

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);

    SharedPtr<vButton> buttonNewGame;
    SharedPtr<vButton> buttonEditor;
    SharedPtr<vButton> buttonExit;
    SharedPtr<vButton> buttonOptions;
};