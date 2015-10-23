#pragma once


#include "GUI/Elements/Window.h"


class lHint : public lWindow
{
    OBJECT(lHint);

public:
    lHint(char *text);

private:
    char *text;
    SharedPtr<lLabel> label;

    void HandleChangeLanguage(StringHash, VariantMap&);
};