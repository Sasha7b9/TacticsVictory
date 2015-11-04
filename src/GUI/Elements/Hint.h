#pragma once


#include "GUI/Elements/Window.h"


class Hint : public lWindow
{
    OBJECT(Hint);

public:
    Hint(char *text);

private:
    char *text;
    SharedPtr<Label> label;

    void HandleChangeLanguage(StringHash, VariantMap&);
};