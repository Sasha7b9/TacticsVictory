#pragma once


#include "GUI/Elements/Window.h"


class Console : public lWindow
{
    OBJECT(Console);

public:
    Console(UContext *context);

    void Toggle();
    void HandleFinishedText(StringHash eventType, VariantMap& eventData);

private:
    SharedPtr<ULineEdit> lineEdit;
    SharedPtr<UText> text;
    SharedPtr<ScrollBar> scrollBar;


};