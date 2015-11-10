#pragma once


class ButtonToggled : public CheckBox
{
    URHO3D_OBJECT(ButtonToggled, CheckBox);

public:
    ButtonToggled(Context *context = gContext);
    ButtonToggled(UIElement *uielement, char *text, int width = -1, int height = -1);

    static void RegisterObject(Context *context = gContext);

    void SetText(char *text);

private:
    ButtonToggled& operator=(const ButtonToggled&) {};

    SharedPtr<Label> label;

    void HandleMouseUp(StringHash eventType, VariantMap &eventData);
};