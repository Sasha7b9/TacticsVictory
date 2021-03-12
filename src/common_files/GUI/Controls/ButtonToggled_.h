// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Label;


class ButtonToggled : public CheckBox
{
    URHO3D_OBJECT(ButtonToggled, CheckBox);

public:
    ButtonToggled(Context *context);
    ButtonToggled(UIElement *uielement, char *text, int width = -1, int height = -1);
    static void RegisterObject();

    void SetText(char *text);

private:
    SharedPtr<Label> label;

    void HandleMouseUp(StringHash eventType, VariantMap &eventData);
};
