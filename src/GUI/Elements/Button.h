#pragma once


class lHint;


class lButton : public Button
{
    OBJECT(lButton);
public:
    lButton(Context *context);
    lButton(UIElement *uielement, char *text, int widht = -1, int height = -1);

    static void RegisterObject(Context *context);

    void SetText(char *text);
    void SetHint(char *text);

    virtual void OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, Cursor* cursor);

private:
    lButton& operator=(const lButton&)
    {};

    SharedPtr<lLabel> label;
    SharedPtr<lHint> hint;

    void HandleHoverBegin(StringHash, VariantMap&);
    void HandleHoverEnd(StringHash, VariantMap&);
    void HandleMouseDown(StringHash, VariantMap&);
};