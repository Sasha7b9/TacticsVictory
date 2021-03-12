// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Button_.h"


class ButtonSwitch : public TButton
{
    URHO3D_OBJECT(ButtonSwitch, TButton);

public:
    ButtonSwitch(Context *context);
    ButtonSwitch(UIElement *uielement, char *text, int width = -1, int height = -1);
    static void RegisterObject();

    void AddState(char *item);
    void SetState(uint state);
    uint GetState();

private:
    PODVector<char*> items;
    uint state = 0;

    void HandleButtonRelease(StringHash, VariantMap&);
};
