// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Hint_.h"


class ButtonT : public Button
{
    URHO3D_OBJECT(ButtonT, Button);

public:

    ButtonT(Context *);
    ButtonT(UIElement *uielement, pchar text, int widht = -1, int height = -1);
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
