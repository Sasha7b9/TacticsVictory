/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Button.h"



class ButtonSwitch : public ButtonRTS
{
    URHO3D_OBJECT(ButtonSwitch, ButtonRTS);

public:
    ButtonSwitch(Context *context = gContext);
    ButtonSwitch(UIElement *uielement, char *text, int width = -1, int height = -1);
    static void RegisterObject(Context *context = gContext);
    void AddState(char *item);
    void SetState(uint state);
    uint GetState();

private:
    PODVector<char*> items;
    uint state = 0;

    void HandleButtonRelease(StringHash, VariantMap&);

    DEFAULT_MEMBERS(ButtonSwitch);
};
