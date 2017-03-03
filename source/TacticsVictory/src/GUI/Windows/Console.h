#pragma once
#include "GUI/Controls/WindowRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConsoleRTS : public WindowRTS
{
    URHO3D_OBJECT(ConsoleRTS, WindowRTS);

public:
    ConsoleRTS(Context *context);
    void Toggle();
    bool IsActive();                            // Возвращает true, если активна строка ввода

private:
    SharedPtr<LineEdit> lineEdit;
    SharedPtr<Text> text;
    SharedPtr<ScrollBar> scrollBar;

    void HandleFinishedText(StringHash, VariantMap&);
};
