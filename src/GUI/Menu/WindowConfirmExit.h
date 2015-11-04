#pragma once


#include "GUI/Elements/Window.h"


class WindowConfirmExit : public lWindow
{
    OBJECT(WindowConfirmExit);

public:
    WindowConfirmExit(UContext *context);

    static void RegisterObject(UContext *context = gContext);

private:
    WindowConfirmExit& operator=(const WindowConfirmExit&)
    {};

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);

    SharedPtr<ButtonMain> buttonOk;
    SharedPtr<ButtonMain> buttonCancel;
};