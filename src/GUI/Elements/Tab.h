#pragma once


#include "GUI/Elements/Window.h"


class lTab : public lWindow
{
    OBJECT(lTab);

public:
    lTab(Context *context);

    static void RegisterObject(Context *context);

    static SharedPtr<lTab> Create(char *title);

    SharedPtr<lButtonToggled> buttonTitle;
};