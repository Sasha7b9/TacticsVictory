#pragma once


#include "GUI/Elements/Window.h"


class WindowConfirmExit : public WindowRTS
{
    URHO3D_OBJECT(WindowConfirmExit, WindowRTS);

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