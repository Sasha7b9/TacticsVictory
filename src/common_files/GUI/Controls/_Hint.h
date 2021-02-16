/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "GUI/Controls/_WindowTV.h"


class Hint : public WindowTV
{
    URHO3D_OBJECT(Hint, WindowTV);

public:
    Hint(char *text);

private:
    char *text = nullptr; //-V122
    SharedPtr<Label> label;

    void HandleChangeLanguage(StringHash, VariantMap&);
};
