#pragma once


#include "GUI/Elements/Window.h"


class tvMenuConfirmExit : public vWindow
{
    OBJECT(tvMenuConfirmExit);

public:
    tvMenuConfirmExit(Context *context);

    static void RegisterObject(Context *context);

private:
    tvMenuConfirmExit& operator=(const tvMenuConfirmExit&)
    {};
};