#pragma once


class lButtonToggled : public CheckBox
{
    OBJECT(lButtonToggled)

public:
    lButtonToggled(Context *context);
    lButtonToggled(UIElement *uielement, char *text, int width = -1, int height = -1);

    static void RegisterObject(Context *context);

    void SetText(char *text);

private:
    lButtonToggled& operator=(const lButtonToggled&) {};

    SharedPtr<lLabel> label;

    void HandleMouseUp(StringHash eventType, VariantMap &eventData);
};