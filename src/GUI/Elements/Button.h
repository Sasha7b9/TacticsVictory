#pragma once


class vButton : public Button
{
    OBJECT(vButton);
public:
    vButton(Context *context);
    vButton(UIElement *uielement, char *text, int widht = -1, int height = -1);

    static void RegisterObject(Context *context);

    void SetText(char *text);

private:
    vButton& operator=(const vButton&)
    {};

    SharedPtr<vLabel> label;

    void HandleHoverBegin(StringHash eventType, VariantMap &eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap &eventData);
    void HandleMouseDown(StringHash eventType, VariantMap &eventData);
};