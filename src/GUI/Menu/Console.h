#pragma once


#include "GUI/Elements/Window.h"


class vConsole : public vWindow
{
    OBJECT(vConsole);

public:
    vConsole(Context *context);

    void Toggle();
    void HandleFinishedText(StringHash eventType, VariantMap& eventData);

private:
    SharedPtr<LineEdit> lineEdit;
    SharedPtr<Text> text;
    SharedPtr<ScrollBar> scrollBar;


};