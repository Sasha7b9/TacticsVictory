#pragma once


#include "GUI/Elements/Window.h"


class Hint : public WindowRTS
{
    URHO3D_OBJECT(Hint, WindowRTS);

public:
    Hint(char *text);

private:
    char *text;
    SharedPtr<Label> label;

    void HandleChangeLanguage(StringHash, VariantMap&);

    CONSTRUCTORS(Hint, WindowRTS);
};