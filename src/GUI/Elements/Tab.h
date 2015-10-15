#pragma once


#include "GUI/Elements/Window.h"


class tvTab : public tvWindow
{
    OBJECT(tvTab);

public:
    tvTab(Context *context);

    static void RegisterObject(Context *context);

    static SharedPtr<tvTab> Create(UIElement *uilement, char *title);

    SharedPtr<tvButtonToggled> buttonTitle;
};