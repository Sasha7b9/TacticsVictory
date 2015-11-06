#pragma once


#include "GUI/Elements/Window.h"


class Console : public lWindow
{
    OBJECT(Console);

public:
    Console(Context *context);

    void Toggle();
    void HandleFinishedText(StringHash eventType, VariantMap& eventData);

private:
    SharedPtr<Urho3D::LineEdit> lineEdit;
    SharedPtr<Urho3D::Text> text;
    SharedPtr<ScrollBar> scrollBar;


};