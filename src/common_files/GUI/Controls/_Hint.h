/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "GUI/Controls/_WindowRTS.h"


class Hint : public WindowRTS
{
    URHO3D_OBJECT(Hint, WindowRTS);

public:
    Hint(char *text);

private:
    char *text = nullptr; //-V122
    SharedPtr<Label> label;

    void HandleChangeLanguage(StringHash, VariantMap&);

    DEFAULT_MEMBERS(Hint);
};
