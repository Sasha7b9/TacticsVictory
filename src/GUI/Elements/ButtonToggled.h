#pragma once


class vButtonToggled : public CheckBox
{
    OBJECT(vButtonToggled)

public:
    vButtonToggled(Context *context);
    vButtonToggled(UIElement *uielement, char *text, int width = -1, int height = -1);

    static void RegisterObject(Context *context);

    void SetText(char *text);

private:
    vButtonToggled& operator=(const vButtonToggled&) {};

    SharedPtr<vLabel> label;

    void HandleMouseUp(StringHash eventType, VariantMap &eventData);
};