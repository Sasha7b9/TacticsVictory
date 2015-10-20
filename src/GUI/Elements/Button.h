#pragma once


class lButton : public Button
{
    OBJECT(lButton);
public:
    lButton(Context *context);
    lButton(UIElement *uielement, char *text, int widht = -1, int height = -1);

    static void RegisterObject(Context *context);

    void SetText(char *text);

private:
    lButton& operator=(const lButton&)
    {};

    SharedPtr<lLabel> label;

    void HandleHoverBegin(StringHash eventType, VariantMap &eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap &eventData);
    void HandleMouseDown(StringHash eventType, VariantMap &eventData);
};