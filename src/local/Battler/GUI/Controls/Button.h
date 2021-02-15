#pragma once
#include "Label.h"
#include "Hint.h"



class ButtonRTS : public Button
{
    URHO3D_OBJECT(ButtonRTS, Button);
public:
    ButtonRTS(Context *context = gContext);
    ButtonRTS(UIElement *uielement, char *text, int widht = -1, int height = -1);
    static void RegisterObject(Context *context = gContext);
    void SetText(char *text);
    void SetHint(char *text);
    virtual void OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButton button,
        MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override;

private:
    SharedPtr<Label> label;
    SharedPtr<Hint> hint;

    void HandleHoverBegin(StringHash, VariantMap&);
    void HandleHoverEnd(StringHash, VariantMap&);

    DEFAULT_MEMBERS(ButtonRTS);
};
