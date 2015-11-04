#pragma once


#include "Label.h"
#include "Hint.h"


class ButtonMain : public UButton
{
    OBJECT(ButtonMain);
public:
    ButtonMain(UContext *context = gContext);
    ButtonMain(UIElement *uielement, char *text, int widht = -1, int height = -1);

    static void RegisterObject(UContext *context = gContext);

    void SetText(char *text);
    void SetHint(char *text);

    virtual void OnClickBegin(const IntVector2& position, const IntVector2& screenPosition, int button, int buttons, int qualifiers, UCursor* cursor);

private:
    ButtonMain& operator=(const ButtonMain&)
    {};

    SharedPtr<Label> label;
    SharedPtr<Hint> hint;

    void HandleHoverBegin(StringHash, VariantMap&);
    void HandleHoverEnd(StringHash, VariantMap&);
};
