#pragma once


#include "ButtonMain.h"


class ButtonSwitch : public ButtonMain
{
    URHO3D_OBJECT(ButtonSwitch, ButtonMain);

public:
    ButtonSwitch(Context *context = gContext);
    ButtonSwitch(UIElement *uielement, char *text, int width = -1, int height = -1);

    static void RegisterObject(Context *context = gContext);

    void AddState(char *item);
    void SetState(uint state);
    uint GetState();

private:
    ButtonSwitch& operator=(const ButtonSwitch&) {};

    PODVector<char*> items;
    uint state = 0;

    void HandleButtonRelease(StringHash, VariantMap&);
};
