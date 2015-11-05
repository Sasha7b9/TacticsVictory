#pragma once


#include "GUI/Elements/Window.h"


class WindowConfirmExit : public lWindow
{
    OBJECT(WindowConfirmExit);

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