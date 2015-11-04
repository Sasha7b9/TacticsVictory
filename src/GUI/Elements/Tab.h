#pragma once


#include "GUI/Elements/Window.h"


class Tab : public lWindow
{
    OBJECT(Tab);

public:
    Tab(UContext *context = gContext);

    static void RegisterObject(UContext *context = gContext);

    static SharedPtr<Tab> Create(char *title);

    SharedPtr<ButtonToggled> buttonTitle;
};