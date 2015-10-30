#pragma once


#include "GUI/Elements/Window.h"


class lWindowConfirmExit : public lWindow
{
    OBJECT(lWindowConfirmExit);

public:
    lWindowConfirmExit(Context *context);

    static void RegisterObject(Context *context = gContext);

private:
    lWindowConfirmExit& operator=(const lWindowConfirmExit&)
    {};

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);

    SharedPtr<lButton> buttonOk;
    SharedPtr<lButton> buttonCancel;
};