#pragma once


#include "GUI/Elements/Window.h"


class lConsole : public lWindow
{
    URHO3D_OBJECT(lConsole, lWindow);

public:
    lConsole(Context *context);

    void Toggle();
    void HandleFinishedText(StringHash eventType, VariantMap& eventData);

private:
    SharedPtr<LineEdit> lineEdit;
    SharedPtr<Text> text;
    SharedPtr<ScrollBar> scrollBar;
};
