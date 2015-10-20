#pragma once


#include "GUI/Elements/Window.h"


class vTab : public vWindow
{
    OBJECT(vTab);

public:
    vTab(Context *context);

    static void RegisterObject(Context *context);

    static SharedPtr<vTab> Create(UIElement *uilement, char *title);

    SharedPtr<vButtonToggled> buttonTitle;
};