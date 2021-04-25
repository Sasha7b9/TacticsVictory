// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Control_.h"


class Hint : public Control
{
    URHO3D_OBJECT(Hint, Control);

public:
    Hint(pchar text);

private:
    char *text = nullptr;
    SharedPtr<Label> label;

    void HandlerChangeLanguage(StringHash, VariantMap&);
};
