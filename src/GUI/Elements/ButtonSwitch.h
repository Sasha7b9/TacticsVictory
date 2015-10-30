#pragma once


#include "Button.h"


class lButtonSwitch : public lButton
{
    OBJECT(lButtonSwitch);

public:
    lButtonSwitch(Context *context = gContext);
    lButtonSwitch(UIElement *uielement, char *text, int width = -1, int height = -1);

    static void RegisterObject(Context *context = gContext);

    void AddState(char *item);
    void SetState(uint state);
    uint GetState();

private:
    lButtonSwitch& operator=(const lButtonSwitch&) {};

    PODVector<char*> items;
    uint state = 0;

    void HandleButtonRelease(StringHash, VariantMap&);
};
