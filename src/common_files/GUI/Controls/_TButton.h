/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "GUI/Controls/_THint.h"


class Label;


class ButtonTV : public Button
{
    URHO3D_OBJECT(ButtonTV, Button);
public:
    ButtonTV(Context *context = TheContext);
    ButtonTV(UIElement *uielement, char *text, int widht = -1, int height = -1);
    static void RegisterObject(Context *context = TheContext);
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
