#pragma once
#include "GUI/Controls/Window.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConsoleRTS : public WindowRTS
{
    URHO3D_OBJECT(ConsoleRTS, WindowRTS);

public:
    ConsoleRTS(Context *context);
    void Toggle();
    void HandleFinishedText(StringHash eventType, VariantMap& eventData);

private:
    SharedPtr<LineEdit> lineEdit;
    SharedPtr<Text> text;
    SharedPtr<ScrollBar> scrollBar;
};
