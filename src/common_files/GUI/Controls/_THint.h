// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/_TWindow.h"


class Hint : public TWindow
{
    URHO3D_OBJECT(Hint, TWindow);

public:
    Hint(char *text);

private:
    char *text = nullptr; //-V122
    SharedPtr<Label> label;

    void HandleChangeLanguage(StringHash, VariantMap&);
};
