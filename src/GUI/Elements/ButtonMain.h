#pragma once


#include "Label.h"
#include "Hint.h"


class ButtonMain : public Urho3D::Button
{
    OBJECT(ButtonMain);
public:
    ButtonMain(Context *context = gContext);
    ButtonMain(UIElement *uielement, char *text, int widht = -1, int height = -1);

    static void RegisterObject(Context *context = gContext);

    void SetText(char *text);
    void SetHint(char *text);

    virtual void OnClickBegin(const UIntVector2& position, const UIntVector2& screenPosition, int button, int buttons, int qualifiers, UCursor* cursor);

private:
    ButtonMain& operator=(const ButtonMain&)
    {};

    SharedPtr<Label> label;
    SharedPtr<Hint> hint;

    void HandleHoverBegin(StringHash, VariantMap&);
    void HandleHoverEnd(StringHash, VariantMap&);
};
