#pragma once


#include "GUI/Elements/Window.h"


class WindowConfirmExit : public lWindow
{
    URHO3D_OBJECT(WindowConfirmExit, lWindow);

public:
    WindowConfirmExit(Context *context);

    static void RegisterObject(Context *context = gContext);

private:
    WindowConfirmExit& operator=(const WindowConfirmExit&)
    {};

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);

    SharedPtr<ButtonMain> buttonOk;
    SharedPtr<ButtonMain> buttonCancel;
};