// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Label;


class TButton : public Button
{
    URHO3D_OBJECT(TButton, Button);
public:
    TButton(Context *context = TheContext);
    TButton(UIElement *uielement, char *text, int widht = -1, int height = -1);
    static void RegisterObject();

    void SetText(char *text);
    void SetHint(char *text);
    virtual void OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button,
        MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override;

private:
    SharedPtr<Label> label;
    SharedPtr<Hint> hint;

    void HandleHoverBegin(StringHash, VariantMap&);
    void HandleHoverEnd(StringHash, VariantMap&);
};
