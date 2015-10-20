#pragma once


#include "GUI/Elements/Window.h"


class lMenuConfirmExit : public lWindow
{
    OBJECT(lMenuConfirmExit);

public:
    lMenuConfirmExit(Context *context);

    static void RegisterObject(Context *context);

private:
    lMenuConfirmExit& operator=(const lMenuConfirmExit&)
    {};

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);

    SharedPtr<lButton> buttonOk;
    SharedPtr<lButton> buttonCancel;
};