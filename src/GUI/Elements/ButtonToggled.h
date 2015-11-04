#pragma once


class ButtonToggled : public UCheckBox
{
    OBJECT(ButtonToggled)

public:
    ButtonToggled(UContext *context = gContext);
    ButtonToggled(UIElement *uielement, char *text, int width = -1, int height = -1);

    static void RegisterObject(UContext *context = gContext);

    void SetText(char *text);

private:
    ButtonToggled& operator=(const ButtonToggled&) {};

    SharedPtr<Label> label;

    void HandleMouseUp(StringHash eventType, VariantMap &eventData);
};