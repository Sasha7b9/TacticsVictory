#pragma once


#include "GUI/Elements/Window.h"


class Hint : public lWindow
{
    URHO3D_OBJECT(Hint, lWindow);

public:
    Hint(char *text);

private:
    char *text;
    SharedPtr<Label> label;

    void HandleChangeLanguage(StringHash, VariantMap&);
};