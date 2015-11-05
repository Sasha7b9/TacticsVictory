#pragma once


#include "GUI/Elements/Window.h"


class Tab : public lWindow
{
    OBJECT(Tab);

public:
    Tab(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    static SharedPtr<Tab> Create(char *title);

    SharedPtr<ButtonToggled> buttonTitle;
};