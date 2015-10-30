#pragma once


#include "Label.h"
#include "Hint.h"


class lButton : public Button
{
    OBJECT(lButton);
public:
    lButton(Context *context = gContext);
    lButton(UIElement *uielement, char *text, int widht = -1, int height = -1);

    static void RegisterObject(Context *context = gContext);

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
};