#pragma once


#include "GUI/Elements/Window.h"


class lTab : public lWindow
{
    OBJECT(lTab);

public:
    lTab(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    static SharedPtr<lTab> Create(char *title);

    SharedPtr<lButtonToggled> buttonTitle;
};