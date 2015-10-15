#pragma once


class tvButton : public Button
{
    OBJECT(tvButton);
public:
    tvButton(Context *context);
    tvButton(UIElement *uielement, char *text, int widht = -1, int height = -1);

    static void RegisterObject(Context *context);

    void SetText(char *text);

private:
    tvButton& operator=(const tvButton&)
    {};

    SharedPtr<tvLabel> label;

    void HandleHoverBegin(StringHash eventType, VariantMap &eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap &eventData);
    void HandleMouseDown(StringHash eventType, VariantMap &eventData);
};