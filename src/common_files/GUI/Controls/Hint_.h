// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Window_.h"


class Hint : public WindowT
{
    URHO3D_OBJECT(Hint, WindowT);

public:
    Hint(char *text);

private:
    char *text = nullptr;
    SharedPtr<Label> label;

    void HandleChangeLanguage(StringHash, VariantMap&);
};
