#pragma once


class tvButtonToggled : public CheckBox
{
    OBJECT(tvButtonToggled)

public:
    tvButtonToggled(Context *context);
    tvButtonToggled(UIElement *uielement, char *text, int width = -1, int height = -1);

    static void RegisterObject(Context *context);

    void SetText(char *text);

private:
    tvButtonToggled& operator=(const tvButtonToggled&) {};

    SharedPtr<tvLabel> label;

    void HandleMouseUp(StringHash eventType, VariantMap &eventData);
};