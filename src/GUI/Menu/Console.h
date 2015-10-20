#pragma once


#include "GUI/Elements/Window.h"


class lConsole : public lWindow
{
    OBJECT(lConsole);

public:
    lConsole(Context *context);

    void Toggle();
    void HandleFinishedText(StringHash eventType, VariantMap& eventData);

private:
    SharedPtr<LineEdit> lineEdit;
    SharedPtr<Text> text;
    SharedPtr<ScrollBar> scrollBar;


};