#pragma once


#include "GUI/Elements/Label.h"


class ButtonToggled : public CheckBox
{
    URHO3D_OBJECT(ButtonToggled, CheckBox);

public:
    ButtonToggled(Context *context = gContext);
    ButtonToggled(UIElement *uielement, char *text, int width = -1, int height = -1);

    static void RegisterObject(Context *context = gContext);

    void SetText(char *text);

private:
    SharedPtr<Label> label;

    void HandleMouseUp(StringHash eventType, VariantMap &eventData);

    CONSTRUCTORS(ButtonToggled, CheckBox);
};