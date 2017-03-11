#pragma once
#include "WindowRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Hint : public WindowRTS
{
    URHO3D_OBJECT(Hint, WindowRTS);

public:
    Hint(char *text);

private:
    char *text = nullptr;
    SharedPtr<Label> label;

    void HandleChangeLanguage(StringHash, VariantMap&);

    DEFAULT_MEMBERS(Hint);
};
